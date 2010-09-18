#include "alertdialog.h"
#include "ui_alertdialog.h"
#include "mailmessageinfo.h"
#include "trackerpreferences.h"

/*!
    \class AlertDialog
    Represents a dialog used to alert the user to new email messages received.
 */

/*!
    Constructs a new alert dialog.
 */
AlertDialog::AlertDialog(TrackerPreferences* settings, QMainWindow* trackerWindow, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AlertDialog),
    m_settings(settings), m_trackerWindow(trackerWindow), m_messages(NULL)
{
    this->ui->setupUi(this);

    // Send all link clicks to our handler
    this->ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    this->setWindowFlags(windowFlags() | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinMaxButtonsHint);

#ifdef Q_OS_MAC
    // Make sure our alert dialog shows on the Mac even if the application window is not visible
    this->setAttribute(Qt::WA_MacAlwaysShowToolWindow, true);
#endif
}

/*!
    Destroys the alert dialog.
 */
AlertDialog::~AlertDialog()
{
    delete this->ui;
    this->freeMessages();
}

void AlertDialog::changeEvent(QEvent* e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            this->ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

/*!
    Shows the alert dialog with the specified list of email messages.
 */
void AlertDialog::show(QList<MailMessageInfo*>* messages)
{
    // This must be called before generateMarkup() or the window won't be resized properly;
    // it needs to be visible before its size is changed since the frame geometry of the window
    // is used to calculate the new size
    QDialog::show();

    // Delete and nullify the previous list of messages
    this->freeMessages();

    // Add the new messages and generate the markup for them
    this->m_messages = messages;
    this->generateMarkup();
}

/*!
    Places the alert form in the bottom-right corner of the screen.
 */
void AlertDialog::snapToCorner()
{
    QRect desktopWorkingArea = QApplication::desktop()->availableGeometry();
    this->move(QPoint(desktopWorkingArea.width() - this->frameGeometry().width(), desktopWorkingArea.height() - this->frameGeometry().height()));
}

/*!
    Generates the XHTML markup used to display a list of the new email messages the user has received.
 */
void AlertDialog::generateMarkup()
{
    QString builder;
    builder.append("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">");
    builder.append("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en-US\" dir=\"ltr\">");
    builder.append("<head><title>New Messages</title></head><body style='background-color: #fff; color: #000; font: 16px Times, serif; margin: 0; padding: 0.75em;'>");
    builder.append(QString("<div style='font-weight: bold; text-align: center;'><a href='#showMainForm'>You have %1 new messages!</a></div><hr /><p></p>").arg(this->m_messages->count()));

    // Add a new DIV element for each email message...
    for (int i = 0; i < this->m_messages->count(); i++)
    {
        MailMessageInfo* message = this->m_messages->at(i);
        builder.append(QString("<div><div style='border-bottom: 1px solid #f00; font-weight: bold;'><span id='messageSubject_%2'>%1</span> - <a href='#blockMessage_%2' style='font-weight: normal;'>Do not alert me about this message</a></div><div style='margin-left: 1em;'><strong>from:</strong> %3<br /><strong>sent at:</strong> %4</div><p></p></div>")
                       .arg(message->subject())
                       .arg(message->id())
                       .arg(message->sender())
                       .arg(message->received().toString("dddd, MMMM d, yyyy 'at' hh:mm AP")));
    }

    builder.append("</body></html>");

    this->ui->webView->setHtml(builder);
}

/*!
    Adjusts the dialog to the correct size and position after loading the HTML content into the web view.
 */
void AlertDialog::loadFinished(bool ok)
{
    // Get the working area of the screen
    QRect desktopWorkingArea = QApplication::desktop()->availableGeometry();

    // First resize the alert dialog to 600x300, then to the size of the web view
    this->resize(600, 30);
    this->resize(this->ui->webView->page()->mainFrame()->contentsSize());

    // Add 30 pixels to the height
    QSize newSize = this->size();
    newSize.setHeight(newSize.height() + 30);

    // If the width of the window is more than 1/3 of the screen width, set it to 1/3 of the screen width
    if (this->size().width() > desktopWorkingArea.width() / 3)
    {
        newSize.setWidth(desktopWorkingArea.width() / 3);
    }

    // If the height of the window is more than 1/2 of the screen height, set it to 1/2 of the screen height
    if (this->size().height() > desktopWorkingArea.height() / 2)
    {
        newSize.setHeight(desktopWorkingArea.height() / 2);
    }

    // Set the new size, and do not allow the user to resize the window
    this->resize(newSize);
    this->setFixedSize(this->width(), this->height());

    // Set the window in the bottom-right corner of the screen
    this->snapToCorner();
}

/*!
    Shows the main window or adds a message to the block list depending on what link was clicked.
 */
void AlertDialog::linkClicked(QUrl url)
{
    // Get the URL the user clicked
    QString str = url.toString();

    // If the link the user clicked was "#showMainForm", show the main window and hide this one
    if (str.indexOf("showMainForm") > -1)
    {
        // If the main window is minimized, bring it to a normal state and activate it
        if (this->m_trackerWindow->windowState() == Qt::WindowMinimized)
        {
            this->m_trackerWindow->setWindowState(Qt::WindowNoState | Qt::WindowActive);
        }

        // Show the main window and hide this one
        this->m_trackerWindow->show();
        this->hide();
    }
    else if (str.indexOf("blockMessage_") > -1)
    {
        // Otherwise if the link the user clicked started with "#blockMessage", rip out the message ID
        int messageId = str.section('_', 1).toInt();

        // Find the index of this message in the array
        int index = -1;
        for (int i = 0; i < this->m_messages->count(); i++)
        {
            if (this->m_messages->at(i)->id() == messageId)
            {
                index = i;
            }
        }

        // Find if it's already in the block list, otherwise we add it
        if (!this->m_settings->containsMessageWithId(messageId))
        {
            this->m_settings->getSuppressedMessages()->append(this->m_messages->at(index));
        }
    }
}

/*!
    Frees all memory and nullifies all references to the email message info instances.
 */
void AlertDialog::freeMessages()
{
    if (this->m_messages)
    {
        for (int i = 0; i < this->m_messages->count(); i++)
        {
            delete this->m_messages->at(i);
        }

        this->m_messages->clear();
        delete this->m_messages;
        this->m_messages = NULL;
    }
}
