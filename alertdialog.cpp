#include "alertdialog.h"
#include "ui_alertdialog.h"
#include "mailmessageinfo.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QWebElement>
#include <QWebFrame>

AlertDialog::AlertDialog(TrackerSettings* settings, QMainWindow* trackerWindow, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AlertDialog)
{
    this->ui->setupUi(this);

    this->settings = settings;
    this->trackerWindow = trackerWindow;

    // Send all link clicks to our handler
    this->ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    this->setWindowFlags(windowFlags() | Qt::Tool | Qt::WindowStaysOnTopHint
        #ifdef Q_OS_MAC
        | Qt::WA_MacAlwaysShowToolWindow
        #endif
    );
}

AlertDialog::~AlertDialog()
{
    delete this->ui;
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

void AlertDialog::show(QList<MailMessageInfo*>* messages)
{
    QDialog::show();
    this->messages = messages;
    this->generateMarkup();
}

/*!
    Places the alert form in the bottom-right corner of the screen.
 */
void AlertDialog::snapToCorner()
{
    QRect desktopWorkingArea = QApplication::desktop()->availableGeometry();
    this->move(*new QPoint(desktopWorkingArea.width() - this->frameGeometry().width(), desktopWorkingArea.height() - this->frameGeometry().height()));
}

void AlertDialog::generateMarkup()
{
    QString builder;
    builder.append("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">");
    builder.append("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en-US\" dir=\"ltr\">");
    builder.append("<head><title>New Messages</title></head><body style='background-color: #fff; color: #000; font: 16px Times, serif; margin: 0; padding: 0.25em;'>");
    builder.append("<div style='margin-left: 2.5em;'>");
    builder.append(QString("<div style='font-weight: bold; text-align: center;'><a href='#showMainForm'>You have %1 new messages!</a></div><hr /><p></p>").arg(messages->count()));

    for (int i = 0; i < this->messages->count(); i++)
    {
        MailMessageInfo* message = this->messages->at(i);
        builder.append(QString("<div><div style='border-bottom: 1px solid #f00; font-weight: bold;'><span id='messageSubject_%2'>%1</span> - <a href='#blockMessage_%2' style='font-weight: normal;'>Do not alert me about this message</a></div><div style='margin-left: 1em;'><strong>from:</strong> %3<br /><strong>sent at:</strong> %4</div><p></p></div>")
                       .arg(message->getSubject())
                       .arg(message->getId())
                       .arg(message->getSender())
                       .arg(message->getReceived().toString("dddd, MMMM d, yyyy 'at' hh:mm AP")));
    }

    builder.append("</div></body></html>");

    this->ui->webView->setHtml(builder);
}

void AlertDialog::loadFinished(bool ok)
{
    QRect desktopWorkingArea = QApplication::desktop()->availableGeometry();

    this->resize(600, 30);
    this->resize(this->ui->webView->page()->mainFrame()->contentsSize());

    QSize newSize = this->size();
    newSize.setHeight(newSize.height() + 30);

    if (this->size().width() > desktopWorkingArea.width() / 3)
    {
        newSize.setWidth(desktopWorkingArea.width() / 3);
    }

    if (this->size().height() > desktopWorkingArea.height() / 2)
    {
        newSize.setHeight(desktopWorkingArea.height() / 2);
    }

    this->resize(newSize);
    this->snapToCorner();
}

void AlertDialog::linkClicked(QUrl url)
{
    QString str = url.toString();

    if (str.indexOf("showMainForm") > -1)
    {
        if (this->trackerWindow->windowState() == Qt::WindowMinimized)
        {
            this->trackerWindow->setWindowState(Qt::WindowNoState | Qt::WindowActive);
        }

        this->trackerWindow->show();
        this->hide();
    }
    else if (str.indexOf("blockMessage_") > -1)
    {
        int messageId = str.section('_', 1).toInt();

        // Find the index of this message in the array
        int index = -1;
        for (int i = 0; i < this->messages->count(); i++)
        {
            if (this->messages->at(i)->getId() == messageId)
            {
                index = i;
            }
        }

        // Find if it's already in the block list, otherwise we add it
        if (!this->settings->containsMessageWithId(messageId))
        {
            this->settings->getSuppressedMessages()->append(this->messages->at(index));
        }
    }
}
