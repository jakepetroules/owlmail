#include "trackerwindow.h"
#include "ui_trackerwindow.h"
#include "alertdialog.h"
#include "mailmessageinfo.h"
#include "trackersettings.h"
#include <QMessageBox>
#include <QWebFrame>
#include <QWebPage>
#include <QWebElement>
#include <QWebElementCollection>
#include <QTimer>
#include <QDateTime>
#include <QSystemTrayIcon>

TrackerWindow::TrackerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackerWindow)
{
    this->ui->setupUi(this);
    this->initialize();
}

TrackerWindow::~TrackerWindow()
{
    delete alertDialog;
    delete ui;
    delete timer;
}

void TrackerWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TrackerWindow::initialize()
{
    // Create the alert dialog
    this->alertDialog = new AlertDialog();

    // Initialize some variables - refresh interval is the time in seconds between each refresh
    this->refreshInterval = 60;
    this->lastRefresh = QDateTime::currentDateTime().toUTC();
    TrackerWindow::kscPage = "http://prod.campuscruiser.com/myksc/";
    TrackerWindow::mailPage = "http://prod.campuscruiser.com/emPageServlet?pg=papp&a=email&cx=u";

    // load 'er up, Scotty! This loads the browser for the first time so the user doesn't wait 60 seconds initially
    this->ui->webView->setUrl(TrackerWindow::kscPage);
    this->ui->webView->setUrl(TrackerWindow::mailPage);
    this->browserReload();

    // Initialize the reload timer, connect the browserReload handler,
    // and start the timer with a 1000 ms (1 second) interval
    this->timer = new QTimer();
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(browserReload()));
    this->timer->start(1000);
}

void TrackerWindow::exit()
{
    this->alertDialog->close();
    this->close();
}

void TrackerWindow::navigateHome()
{
    this->ui->webView->setUrl(TrackerWindow::kscPage);
}

void TrackerWindow::navigateInbox()
{
    this->ui->webView->setUrl(TrackerWindow::mailPage);
}

void TrackerWindow::options()
{

}

void TrackerWindow::checkForUpdates()
{

}

void TrackerWindow::about()
{
    QMessageBox::about(this, this->windowTitle(), "KSC Email Tracker v1.1b");
}

void TrackerWindow::browserReload()
{
    int timeToRefresh = QDateTime::currentDateTime().toUTC().secsTo(this->lastRefresh.addSecs(this->refreshInterval));

    // Prevent system clock changes from stopping the program operating normally
    if (timeToRefresh > this->refreshInterval)
    {
        this->lastRefresh = QDateTime::currentDateTime().toUTC();
        return;
    }

    // If we're past the last refresh time plus the refresh interval, refresh again
    if (QDateTime::currentDateTime().toUTC() >= this->lastRefresh.addSecs(this->refreshInterval))
    {
        // Navigate to the current URL (this works better than refreshing)
        this->ui->webView->setUrl(TrackerWindow::mailPage);

        // ...and update the last refresh time
        this->lastRefresh = QDateTime::currentDateTime().toUTC();
    }

    // Update the "time to refresh" label
    this->ui->timeLabel->setText(QString::number(timeToRefresh) + " seconds until refresh");

    // The rest of this code only lets you postpone the page reload (useful
    // if you are in the middle of writing an email) unless the remaining time
    // is half or less of the refresh interval. For example, if the interval
    // is 1 minute (default), you can only postpone when the remaining time is
    // 40 seconds or less. This is again, not a perfect system, as, if you're
    // not paying attention, your email is erased. For this reason it is
    // recommended to use your browser to write emails, and use this program
    // as an alert system ONLY.
    if (timeToRefresh < 30)
    {
        this->ui->timeLabel->setText("<span style='color: red;'>" + this->ui->timeLabel->text() + "</span>");
    }

    //buttonPostpone.Enabled = ((this.lastRefresh + this.refreshInterval) - DateTime.UtcNow).TotalSeconds < (this.refreshInterval.TotalSeconds / 2);
}

void TrackerWindow::browserLoaded(bool ok)
{
    // If we are not logged in (the page contains the "Log In" header or the log in icon)
    QString documentHtml = this->ui->webView->page()->mainFrame()->toHtml();
    if (documentHtml.contains("Log In</H1>") || documentHtml.contains("icon_signin_secure.gif"))
    {
        // Read username and password from settings file and inject values into webpage
        TrackerSettings::read();

        this->ui->webView->page()->mainFrame()->findFirstElement("#userName").setAttribute("value", TrackerSettings::getUsername());
        this->ui->webView->page()->mainFrame()->findFirstElement("#password").setAttribute("value", TrackerSettings::getPassword());

        // If the page does NOT contain the "invalid password/credentials" string, submit the form -
        // we don't want to submit the wrong password over and over and get the user's account locked
        if (!documentHtml.contains("Invalid log in or password.") && !documentHtml.contains("Invalid Credentials"))
        {
            // Loop through all the inputs on the page
            QWebElementCollection inputs = this->ui->webView->page()->mainFrame()->findAllElements("input");
            for (int i = 0; i < inputs.count(); i++)
            {
                // If this is the submit button, click it
                if (inputs.at(i).attribute("type") == "submit" && inputs.at(i).attribute("value") == "Log In")
                {
                    inputs.at(i).evaluateJavaScript("this.click();");
                }
            }
        }
    }
    else
    {
        QList<MailMessageInfo>* unreadMessages = new QList<MailMessageInfo>();

        QWebElement messageTable = this->ui->webView->page()->mainFrame()->documentElement().findFirst("#mailList");
        QWebElementCollection messageTableRows = messageTable.findAll("tr");
        for (int i = 0; i < messageTableRows.count(); i++)
        {
            QWebElementCollection cells = messageTableRows.at(i).findAll("td");

            int mailId = messageTableRows.at(i).findFirst("input").attribute("value").toInt();
            QString mailSender = cells.at(2).toPlainText();
            QString mailSubject = cells.at(3).toPlainText();
            QDateTime mailDateTime = QDateTime::fromString(cells.at(4).toPlainText(), "MM/dd/yyyy hh:mm AP");

            // We only want unread messages and ones that aren't stopped from alerting about
            TrackerSettings::read();
            if (cells.at(1).firstChild().attribute("alt") == "Unread" && !TrackerSettings::getSuppressedMessages()->contains(mailId))
            {
                MailMessageInfo* info = new MailMessageInfo(mailId, mailSender, mailSubject, mailDateTime);
                unreadMessages->append(*info);
            }
        }

        if (unreadMessages->count() > 0)
        {
            this->alertDialog->show(unreadMessages);
        }
    }
}
