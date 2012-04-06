#include "owlmailapplication.h"
#include "trackerpreferences.h"
#include "version.h"
#include "mainwindow.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/preferencesdialog.h"
#include "dialogs/updatedialog.h"

class OwlMailApplication::Private
{
public:
    Private() : updateDialog(NULL) { }
    UpdateDialog *updateDialog;
};

OwlMailApplication::OwlMailApplication(int &argc, char *argv[]) :
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

    this->setUrl(OrganizationHomePage, QUrl("http://www.ksccsclub.com/"));
    this->setUrl(OrganizationDonations, QUrl("http://www.ksccsclub.com/"));
    this->setUrl(ApplicationHomePage, QUrl("http://ksccsclub.github.com/owlmail"));
    this->setUrl(ApplicationHelp, QUrl("http://ksccsclub.github.com/owlmail"));
    this->setUrl(ApplicationUpdate, QUrl("http://ksccsclub.github.com/owlmail"));

    // Create the update dialog and have it do a check within 5 seconds if this was selected in the options
    this->d->updateDialog = new UpdateDialog(NULL);
    this->d->updateDialog->setWindowModality(Qt::ApplicationModal);
    if (UpdateDialog::automaticUpdatesSupported() && TrackerPreferences::instance().updateOnStartup())
    {
        QTimer::singleShot(5000, this, SLOT(checkForUpdatesSilent()));
    }
}

OwlMailApplication::~OwlMailApplication()
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

bool OwlMailApplication::handleReopen(bool hasVisibleWindows)
{
    if (!hasVisibleWindows)
    {
        this->showMainWindow();
    }

    return true;
}

void OwlMailApplication::showHelpContents()
{
    QDesktopServices::openUrl(this->url(ApplicationHelp));
}

void OwlMailApplication::launchProductWebsite()
{
    QDesktopServices::openUrl(this->url(ApplicationHomePage));
}

void OwlMailApplication::launchDonationsWebsite()
{
    QDesktopServices::openUrl(this->url(OrganizationDonations));
}

/*!
    Displays the check for updates dialog.
 */
void OwlMailApplication::checkForUpdates()
{
    this->d->updateDialog->show();
    this->checkForUpdatesSilent();
}

/*!
    Checks for updates and only shows the dialog if an update is available.
 */
void OwlMailApplication::checkForUpdatesSilent()
{
    this->d->updateDialog->check();
}

void OwlMailApplication::preferences()
{
    PreferencesDialog preferences;
    preferences.exec();
}

void OwlMailApplication::about()
{
    AboutDialog dialog;
    dialog.exec();
}

bool OwlMailApplication::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::ApplicationActivate:
        this->showMainWindow();
        break;
    default:
        break;
    }

    return IntegratedApplication::event(event);
}

void OwlMailApplication::showMainWindow()
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
