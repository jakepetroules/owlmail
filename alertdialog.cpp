#include "alertdialog.h"
#include "ui_alertdialog.h"
#include "mailmessageinfo.h"
#include <QDesktopWidget>
#include <QWebFrame>

AlertDialog::AlertDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::AlertDialog)
{
    this->ui->setupUi(this);

    this->setWindowFlags(windowFlags() | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
}

AlertDialog::~AlertDialog()
{
    delete ui;
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

void AlertDialog::show(QList<MailMessageInfo>* messages)
{
    QDialog::show();
    this->generateMarkup(messages);
}

/*!
    Places the alert form in the bottom-right corner of the screen.
 */
void AlertDialog::snapToCorner()
{
    QRect desktopWorkingArea = QApplication::desktop()->availableGeometry();
    this->move(*new QPoint(desktopWorkingArea.width() - this->frameGeometry().width(), desktopWorkingArea.height() - this->frameGeometry().height()));
}

void AlertDialog::generateMarkup(QList<MailMessageInfo>* messages)
{
    QString builder;
    builder.append("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">");
    builder.append("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en-US\" dir=\"ltr\">");
    builder.append("<head><title>New Messages</title></head><body style='background-color: #fff; color: #000; font: 16px Times, serif; margin: 0; padding: 0.25em;'>");
    builder.append("<div style='margin-left: 2.5em;'>");
    builder.append(QString("<div style='font-weight: bold; text-align: center;'><a id='showMainForm' href='#'>You have %1 new messages!</a></div><hr /><p></p>").arg(messages->count()));

    for (int i = 0; i < messages->count(); i++)
    {
        MailMessageInfo message = messages->at(i);
        builder.append(QString("<div><div style='border-bottom: 1px solid #f00; font-weight: bold;'><span id='messageSubject_%2'>%1</span> - <a href='#' id='blockMessage_%2' style='font-weight: normal;'>Do not alert me about this message</a></div><div style='margin-left: 1em;'><strong>from:</strong> %3<br /><strong>sent at:</strong> %4</div><p></p></div>")
                       .arg(message.getSubject())
                       .arg(message.getId())
                       .arg(message.getSender())
                       .arg(message.getReceived().toString("dddd, MMMM d, yyyy 'at' hh:mm AP")));
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
    /*
    HtmlElement element = this.webBrowserAlert.Document.GetElementFromPoint(e.ClientMousePosition);
    if (element != null && element.Id != null)
    {
        if (element.Id == "showMainForm")
        {
            this.MainForm.Show();

            if (this.MainForm.WindowState == FormWindowState.Minimized)
            {
                this.MainForm.WindowState = FormWindowState.Normal;
            }

            this.MainForm.BringToFront();
            this.Hide();
        }
        else if (element.Id.StartsWith("blockMessage_"))
        {
            int messageId = Convert.ToInt32(element.Id.Replace("blockMessage_", string.Empty));

            if (!TrackerSettings.NonAlertedMessages.ContainsId(messageId))
            {
                TrackerSettings.Read();
                TrackerSettings.NonAlertedMessages.Add(new MailMessageInfo() { Id = messageId, Subject = this.webBrowserAlert.Document.GetElementById("messageSubject_" + messageId).InnerText });
                TrackerSettings.Write();
            }
        }
    }*/
}
