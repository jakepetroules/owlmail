#include "trackerwindow.h"
#include "ui_trackerwindow.h"
#include "aboutdialog.h"
#include "alertdialog.h"
#include "mailmessageinfo.h"
#include "optionsdialog.h"
#include "trackersettings.h"
#include "version.h"
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QWebFrame>
#include <QWebPage>
#include <QWebElement>
#include <QWebElementCollection>

#define KSC_PAGE "http://prod.campuscruiser.com/myksc/"
#define INITIAL_MAIL_PAGE "http://prod.campuscruiser.com/emPageServlet?pg=papp&a=email&cx=u&cp=160"
#define MAIL_PAGE "http://prod.campuscruiser.com/emPageServlet?cx=u&pg=papp&tg=Email-checkmail&cmd=checkmail"

/*!
    \class TrackerWindow
    Represents the main window of the KSC Email Tracker application.
 */

/*!
    Constructs an email tracker window.
 */
TrackerWindow::TrackerWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::TrackerWindow),
    m_settings(new TrackerSettings()), m_trayIcon(new QSystemTrayIcon(this)), m_alertDialog(new AlertDialog(this->m_settings, this)),
    m_timer(new QTimer()), m_manager(new QNetworkAccessManager(this))
{
    // Set information about the application
    QCoreApplication::setOrganizationName(VER_COMPANYNAME_STR);
    QCoreApplication::setOrganizationDomain(VER_COMPANYDOMAIN_STR);
    QCoreApplication::setApplicationName(VER_PRODUCTNAME_STR);
    QCoreApplication::setApplicationVersion(VER_PRODUCTVERSION_STR);

    // Setup the user interface
    this->ui->setupUi(this);

    #ifdef Q_WS_X11
    // Actions
    this->ui->actionE_xit->setIcon(QIcon::fromTheme("application-exit"));
    this->ui->actionOptions->setIcon(QIcon::fromTheme("preferences-other"));
    this->ui->actionAbout->setIcon(QIcon::fromTheme("help-about"));
    #endif

    // Keyboard Shortcuts
    this->ui->actionE_xit->setShortcut(QKeySequence::Quit);
    this->ui->actionMyKSC_Inbox->setShortcut(QKeySequence::Back);
    this->ui->actionOptions->setShortcut(QKeySequence::Preferences);

    // Read the settings from the file
    this->m_settings->read();

    // Initialize the tray icon
    this->initializeTrayIcon();

    // Initialize the program
    this->initialize();

    // Move the application window to the center of the screen
    QRect rect = this->frameGeometry();
    rect.moveCenter(QDesktopWidget().availableGeometry().center());
    this->move(rect.topLeft());

    // Connect slots and signals
    QObject::connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(beforeExit()));
    QObject::connect(this->m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

/*!
    Destroys the TrackerWindow.
 */
TrackerWindow::~TrackerWindow()
{
    delete this->m_alertDialog;
    delete this->ui;
    delete this->m_timer;
    delete this->m_settings;
    delete this->m_trayIcon;
    delete this->m_manager;
}

void TrackerWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
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
    Stops the application from closing when the close button is clicked, allowing it to continue running in the background.
 */
void TrackerWindow::closeEvent(QCloseEvent* event)
{
    if (this->m_trayIcon->isVisible())
    {
        event->ignore();
        this->hide();

        this->m_trayIcon->showMessage("MyKSC Email Tracker", "MyKSC Email Tracker is still running. To fully exit the program right click this icon and select exit.", QSystemTrayIcon::Information);
    }
}

/*!
    Shows the main window when the tray icon is triggered (clicked) or double clicked.
 */
void TrackerWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->show();
            break;
        default:
            break;
    }
}

/*!
    Initializes the system tray icon.
 */
void TrackerWindow::initializeTrayIcon()
{
    this->m_trayIcon->setIcon(this->windowIcon());
    this->m_trayIcon->setToolTip(this->windowTitle());
    this->m_trayIcon->setContextMenu(this->ui->menu_File);
    this->m_trayIcon->show();

    // Connect our icon activated event so we can re-show the window when the user double clicks the icon
    QObject::connect(this->m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

/*!
    Initializes the application.
 */
void TrackerWindow::initialize()
{
    // Initialize some variables - refresh interval is the time in seconds between each refresh
    this->m_refreshInterval = 60;
    this->m_lastRefresh = QDateTime::currentDateTime().toUTC();

    // load 'er up, Scotty! This loads the browser for the first time so the user doesn't wait 60 seconds initially
    this->ui->webView->setUrl(QString(INITIAL_MAIL_PAGE));
    this->browserReload();

    // Initialize the reload timer, connect the browserReload handler,
    // and start the timer with a 1000 ms (1 second) interval
    QObject::connect(this->m_timer, SIGNAL(timeout()), this, SLOT(browserReload()));
    this->m_timer->start(1000);
}

/*!
    Performs operations before the program exits.
 */
void TrackerWindow::beforeExit()
{
    this->m_settings->write();
}

/*!
    Exits the application.
 */
void TrackerWindow::exit()
{
    QApplication::closeAllWindows();
    QApplication::exit();
    QApplication::quit();
}

/*!
    Navigates to the MyKSC home page.
 */
void TrackerWindow::navigateHome()
{
    this->ui->webView->setUrl(QString(KSC_PAGE));
}

/*!
    Navigates to the MyKSC email inbox.
 */
void TrackerWindow::navigateInbox()
{
    this->ui->webView->setUrl(QString(MAIL_PAGE));
}

/*!
    Launches the options dialog.
 */
void TrackerWindow::options()
{
    OptionsDialog* dialog = new OptionsDialog(this->m_settings, this);
    dialog->exec();
    delete dialog;
}

/*!
    Launches the check for updates dialog.
 */
void TrackerWindow::checkForUpdates()
{
    if (QMessageBox::information(this, this->windowTitle(),
        QString("You are running %1 version %2. Would you like to open the project's page in your web browser to see if a newer version is available?")
        .arg(QApplication::applicationName())
        .arg(QApplication::applicationVersion()),
        QMessageBox::Yes,
        QMessageBox::No) == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl("http://www.petroules.com/products/kscemailtracker/"));
    }
}

/*!
    Shows the program's about dialog.
 */
void TrackerWindow::about()
{
    QString str = "<p>KSC Email Tracker is an application designed to allow Keene State College students to manage their email more effectively.</p>";
    str.append("<p>The owl icon used in this program is a public domain image. Details can be found <a href=\"http://www.openclipart.org/detail/17566\">here</a>.</p>");
    AboutDialog::show(this, this->windowTitle(), str);
}

/*!
    Manages timer text updating and page refreshing.
 */
void TrackerWindow::browserReload()
{
    int timeToRefresh = QDateTime::currentDateTime().toUTC().secsTo(this->m_lastRefresh.addSecs(this->m_refreshInterval));

    // Prevent system clock changes from stopping the program operating normally
    if (timeToRefresh > this->m_refreshInterval)
    {
        this->m_lastRefresh = QDateTime::currentDateTime().toUTC();
        return;
    }

    // If we're past the last refresh time plus the refresh interval, refresh again
    if (QDateTime::currentDateTime().toUTC() >= this->m_lastRefresh.addSecs(this->m_refreshInterval))
    {
        // Navigate to the current URL (this works better than refreshing)
        this->ui->webView->setUrl(QString(MAIL_PAGE));

        // ...and update the last refresh time
        this->m_lastRefresh = QDateTime::currentDateTime().toUTC();
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

    this->ui->postponeButton->setEnabled(timeToRefresh < (this->m_refreshInterval / 2));
}

/*!
    Performs checking operations that determine if alerts need to be shown, every time the program is reloaded.
 */
void TrackerWindow::browserLoaded(bool ok)
{
    QString documentHtml = this->ui->webView->page()->mainFrame()->toHtml();
    if (documentHtml.contains("Invalid context.") && documentHtml.contains("No E-mail Found."))
    {
        this->ui->webView->setUrl(QString(MAIL_PAGE));
        return;
    }

    // If we are not logged in (the page contains the "Log In" header or the log in icon)
    if (documentHtml.contains("Log In</H1>") || documentHtml.contains("icon_signin_secure.gif"))
    {
        // Read username and password from settings file and inject values into webpage
        this->ui->webView->page()->mainFrame()->findFirstElement("#userName").setAttribute("value", this->m_settings->getUsername());
        this->ui->webView->page()->mainFrame()->findFirstElement("#password").setAttribute("value", this->m_settings->getPassword());

        // We only want to submit if the username and password are BOTH not blank
        // That way a user can store their username only and manually enter their password (which is more secure)
        if (this->m_settings->getUsername() != "" && this->m_settings->getPassword() != "")
        {
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
    }
    else
    {
        QList<MailMessageInfo*>* unreadMessages = new QList<MailMessageInfo*>();

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
            if (cells.at(1).firstChild().attribute("alt") == "Unread" && !this->m_settings->containsMessageWithId(mailId))
            {
                MailMessageInfo* info = new MailMessageInfo(mailId, mailSender, mailSubject, mailDateTime);
                unreadMessages->append(info);
            }
        }

        if (unreadMessages->count() > 0)
        {
            this->m_alertDialog->show(unreadMessages);
        }
    }

    QNetworkRequest* request = new QNetworkRequest(QUrl("http://www.petroules.com/robots.txt"));
    request->setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i386; en-US; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3");
    this->m_manager->get(*request);
    delete request;
}

void TrackerWindow::replyFinished(QNetworkReply* reply)
{
    qDebug() << QString(reply->readAll());
}

/*!
    Adds the refresh interval to the remaining time until refresh, when the postpone button is clicked.
 */
void TrackerWindow::postponeButtonClicked(bool ok)
{
    this->m_lastRefresh = this->m_lastRefresh.addSecs(this->m_refreshInterval);
    this->ui->postponeButton->setEnabled(false);
}
