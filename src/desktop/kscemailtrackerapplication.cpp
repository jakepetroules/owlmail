#include "kscemailtrackerapplication.h"
#include "trackerpreferences.h"
#include "version.h"
#include "mainwindow.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/preferencesdialog.h"
#include "dialogs/updatedialog.h"

class KSCEmailTrackerApplication::Private
{
public:
    Private() : updateDialog(NULL) { }
    UpdateDialog *updateDialog;
};

KSCEmailTrackerApplication::KSCEmailTrackerApplication(int &argc, char *argv[]) :
    IntegratedApplication(VER_APP_UUID, argc, argv), d(new Private())
{
    Q_INIT_RESOURCE(globalresources);
    Q_INIT_RESOURCE(resources);

    this->setOrganizationName(VER_COMPANYNAME_STR);
    this->setOrganizationDomain(VER_COMPANYDOMAIN_STR);
    this->setApplicationName(APP_DISPLAYNAME);
    this->setUnixName(APP_UNIXNAME);
    this->setBundleId(APP_BUNDLEID);
    this->setApplicationVersion(QVersion(VER_PRODUCTVERSION_STR));
    this->setFileVersion(QVersion(VER_FILEVERSION_STR));
    this->setCopyright(VER_LEGALCOPYRIGHT_STR);
    this->setTrademarks(VER_LEGALTRADEMARKS1_STR);

    this->setUrl(OrganizationHomePage, QUrl("http://www.petroules.com/"));
    this->setUrl(OrganizationDonations, QUrl("http://www.petroules.com/donate"));
    this->setUrl(ApplicationHomePage, QUrl("http://www.petroules.com/products/kscemailtracker"));
    this->setUrl(ApplicationHelp, QUrl("http://www.petroules.com/support/kscemailtracker"));
    this->setUrl(ApplicationUpdate, QUrl("https://www.petroules.com/version/kscemailtracker/"));

    // Create the update dialog and have it do a check within 5 seconds if this was selected in the options
    this->d->updateDialog = new UpdateDialog(NULL);
    this->d->updateDialog->setWindowModality(Qt::ApplicationModal);
    if (UpdateDialog::automaticUpdatesSupported() && TrackerPreferences::instance().updateOnStartup())
    {
        QTimer::singleShot(5000, this, SLOT(checkForUpdatesSilent()));
    }
}

KSCEmailTrackerApplication::~KSCEmailTrackerApplication()
{
    if (this->d)
    {
        if (this->d->updateDialog)
        {
            delete this->d->updateDialog;
        }

        delete this->d;
    }

    // Save all preferences and free memory
    TrackerPreferences::instance().destroy();
}

void KSCEmailTrackerApplication::showHelpContents()
{
    QDesktopServices::openUrl(this->url(ApplicationHelp));
}

void KSCEmailTrackerApplication::launchProductWebsite()
{
    QDesktopServices::openUrl(this->url(ApplicationHomePage));
}

void KSCEmailTrackerApplication::launchDonationsWebsite()
{
    QDesktopServices::openUrl(this->url(OrganizationDonations));
}

/*!
    Displays the check for updates dialog.
 */
void KSCEmailTrackerApplication::checkForUpdates()
{
    this->d->updateDialog->show();
    this->checkForUpdatesSilent();
}

/*!
    Checks for updates and only shows the dialog if an update is available.
 */
void KSCEmailTrackerApplication::checkForUpdatesSilent()
{
    this->d->updateDialog->check();
}

void KSCEmailTrackerApplication::preferences()
{
    PreferencesDialog preferences;
    preferences.exec();
}

void KSCEmailTrackerApplication::about()
{
    AboutDialog dialog;
    dialog.exec();
}

bool KSCEmailTrackerApplication::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ApplicationActivate:
        this->showMainWindow();
        break;
    }

    event->accept();
    return true;
}

void KSCEmailTrackerApplication::showMainWindow()
{
    foreach (QWidget *widget, this->topLevelWidgets())
    {
        MainWindow *window = qobject_cast<MainWindow*>(widget);
        if (window)
        {
            window->show();
        }
    }
}
