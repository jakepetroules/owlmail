#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "owlmailapplication.h"
#include "mailmessageinfo.h"
#include "trackerpreferences.h"
#include "trackerwebpage.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/alertdialog.h"
#include "dialogs/preferencesdialog.h"
#include "dialogs/updatedialog.h"
#include "version.h"
#include <petroules-utilities.h>

#define KSC_PAGE "http://prod.campuscruiser.com/myksc/"
#define INITIAL_MAIL_PAGE "http://prod.campuscruiser.com/emPageServlet?pg=papp&a=email&cx=u&cp=160"
#define MAIL_PAGE "http://prod.campuscruiser.com/emPageServlet?cx=u&pg=papp&tg=Email-checkmail&cmd=checkmail"

/*!
    \class MainWindow

    Represents the main window of the application.
 */

/*!
    Constructs an new MainWindow.
 */
MainWindow::MainWindow(QWidget* parent) :
    IntegratedMainWindow(parent),
    ui(new Ui::MainWindow),
    m_trayIcon(new QSystemTrayIcon(this)), m_alertDialog(new AlertDialog(this)),
    m_timer(new QTimer())
{
    this->ui->setupUi(this);
    WindowManager::centerMainWindow(this);
    this->updateSingleInstance();

#ifdef Q_WS_X11
    // Actions
    this->ui->actionExit->setIcon(QIcon::fromTheme("application-exit"));
    this->ui->actionOptions->setIcon(QIcon::fromTheme("preferences-other"));
    this->ui->actionAbout->setIcon(QIcon::fromTheme("help-about"));
#endif

    // Keyboard Shortcuts
    this->ui->actionExit->setShortcut(QKeySequence::Quit);
    this->ui->actionOptions->setShortcut(QKeySequence::Preferences);

    // Initialize the tray icon
    this->initializeTrayIcon();

    // Initialize the program
    this->initialize();
}

/*!
    Destroys the MainWindow.
 */
MainWindow::~MainWindow()
{
    delete this->m_alertDialog;
    delete this->ui;
    delete this->m_timer;
    delete this->m_trayIcon;
}

void MainWindow::changeEvent(QEvent* e)
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
    Stops the application from closing when the close button is clicked,
    allowing it to continue running in the background.
 */
void MainWindow::closeEvent(QCloseEvent* event)
{
    if (this->m_trayIcon->isVisible())
    {
        event->ignore();
        this->hide();

        this->m_trayIcon->showMessage(qiApp->applicationName(),
            tr("%1 is still running. To exit the program right click this icon and select exit.")
            .arg(qiApp->applicationName()), QSystemTrayIcon::Information);
    }
}

/*!
    Shows the main window when the tray icon is triggered (clicked) or double clicked.
 */
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        {
            this->setVisible(!this->isVisible());
            if (this->isVisible())
            {
                this->setWindowState(this->windowState() & ~Qt::WindowMinimized);
                this->raise();
                this->activateWindow();
            }

            break;
        }
        default:
            break;
    }
}

void MainWindow::handleMessage(const QString &message)
{
    Q_UNUSED(message);

    emit this->needToShow();
}

void MainWindow::updateSingleInstance(MainWindow *mw)
{
    IntegratedApplication *singleApp = qiApp;
    if (singleApp)
    {
        // Remove any previous messageReceived signal handler and reconnect it to the specified MainWindow
        QObject::disconnect(singleApp, SIGNAL(messageReceived(const QString&)), NULL, NULL);
        QObject::connect(singleApp, SIGNAL(messageReceived(const QString&)), mw, SLOT(handleMessage(const QString&)));

        // Set the activation window to the specified one
        singleApp->setActivationWindow(mw, false);

        // Connect our needToShow signal
        QObject::connect(mw, SIGNAL(needToShow()), singleApp, SLOT(activateWindow()));
    }
}

/*!
    Initializes the system tray icon.
 */
void MainWindow::initializeTrayIcon()
{
#ifndef Q_WS_MAC
    this->m_trayIcon->setIcon(this->windowIcon());
    this->m_trayIcon->setToolTip(this->windowTitle());
    this->m_trayIcon->setContextMenu(this->ui->menuFile);
    this->m_trayIcon->show();

    // Connect our icon activated event so we can re-show the window when the user double clicks the icon
    QObject::connect(this->m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
#endif
}

/*!
    Initializes the application.
 */
void MainWindow::initialize()
{
    // Initialize some variables - refresh interval is the time in seconds between each refresh
    this->m_refreshInterval = 60;
    this->m_lastRefresh = QDateTime::currentDateTime().toUTC();

    // This loads the browser for the first time so the user doesn't wait 60 seconds initially
    TrackerWebPage *page = new TrackerWebPage(this);
    this->ui->webView->setPage(page);
    this->ui->webView->setUrl(QString(INITIAL_MAIL_PAGE));
    this->browserReload();

    // Initialize the reload timer, connect the browserReload handler,
    // and start the timer with a 1000 ms (1 second) interval
    QObject::connect(this->m_timer, SIGNAL(timeout()), this, SLOT(browserReload()));
    this->m_timer->start(1000);

    this->setNativeFullScreenEnabled(true);
}

/*!
    Exits the application.
 */
void MainWindow::exit()
{
    QApplication::closeAllWindows();
    QApplication::exit();
    QApplication::quit();
}

/*!
    Navigates to the MyKSC home page.
 */
void MainWindow::navigateHome()
{
    this->ui->webView->setUrl(QString(KSC_PAGE));
}

/*!
    Navigates to the MyKSC email inbox.
 */
void MainWindow::navigateInbox()
{
    this->ui->webView->setUrl(QString(MAIL_PAGE));
}

/*!
    Launches the options dialog.
 */
void MainWindow::options()
{
    qkApp->preferences();
}

void MainWindow::help()
{
    qkApp->showHelpContents();
}

void MainWindow::website()
{
    qkApp->launchProductWebsite();
}

void MainWindow::donate()
{
    qkApp->launchDonationsWebsite();
}

/*!
    Launches the check for updates dialog.
 */
void MainWindow::checkForUpdates()
{
    qkApp->checkForUpdates();
}

/*!
    Shows the program's about dialog.
 */
void MainWindow::about()
{
    qkApp->about();
}

/*!
    Manages timer text updating and page refreshing.
 */
void MainWindow::browserReload()
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
        this->ui->timeLabel->setText("<font color='red'>" + this->ui->timeLabel->text() + "</font>");
    }

    this->ui->postponeButton->setEnabled(timeToRefresh < (this->m_refreshInterval / 2));
}

/*!
    Performs checking operations that determine if alerts need to be shown, every time the program is reloaded.
 */
void MainWindow::browserLoaded(bool ok)
{
    Q_UNUSED(ok);

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
        this->ui->webView->page()->mainFrame()->findFirstElement("#userName").setAttribute("value", TrackerPreferences::instance().username());
        this->ui->webView->page()->mainFrame()->findFirstElement("#password").setAttribute("value", TrackerPreferences::instance().password());

        // We only want to submit if the username and password are BOTH not blank
        // That way a user can store their username only and manually enter their password (which is more secure)
        if (TrackerPreferences::instance().username() != "" && TrackerPreferences::instance().password() != "")
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
            if (cells.at(1).firstChild().attribute("alt") == "Unread" && !TrackerPreferences::instance().containsMessageWithId(mailId))
            {
                MailMessageInfo* info = new MailMessageInfo(mailId, mailSender, mailSubject, mailDateTime);
                unreadMessages->append(info);
            }
        }

        if (unreadMessages->count() > 0)
        {
            this->m_alertDialog->show(unreadMessages);
            QApplication::alert(this);

            qkApp->setBadgeText(unreadMessages->count());
        }
        else
        {
            qkApp->clearBadgeText();
        }
    }
}

/*!
    Adds the refresh interval to the remaining time until refresh, when the postpone button is clicked.
 */
void MainWindow::postponeButtonClicked(bool ok)
{
    Q_UNUSED(ok);

    this->m_lastRefresh = this->m_lastRefresh.addSecs(this->m_refreshInterval);
    this->ui->postponeButton->setEnabled(false);
}
