#include <QtGui>
#include <QtSingleApplication>
#include "mainwindow.h"
#include "version.h"
#include <liel.h>

void setAppInfo()
{
    ApplicationInfo::setOrganizationName(VER_COMPANYNAME_STR);
    ApplicationInfo::setOrganizationDomain(VER_COMPANYDOMAIN_STR);
    ApplicationInfo::setApplicationName(APP_DISPLAYNAME);
    ApplicationInfo::setUnixName(APP_UNIXNAME);
    ApplicationInfo::setBundleId(APP_BUNDLEID);
    ApplicationInfo::setApplicationVersion(QVersion(VER_PRODUCTVERSION_STR));
    ApplicationInfo::setFileVersion(QVersion(VER_FILEVERSION_STR));
    ApplicationInfo::setCopyright(VER_LEGALCOPYRIGHT_STR);
    ApplicationInfo::setTrademarks(VER_LEGALTRADEMARKS1_STR);

    ApplicationInfo::setUrl(ApplicationInfo::OrganizationHomePage, QUrl("http://www.petroules.com/"));
    ApplicationInfo::setUrl(ApplicationInfo::OrganizationDonations, QUrl("http://www.petroules.com/donate/"));
    ApplicationInfo::setUrl(ApplicationInfo::ApplicationHomePage, QUrl("http://www.petroules.com/products/kscemailtracker/"));
    ApplicationInfo::setUrl(ApplicationInfo::ApplicationHelp, QUrl("http://www.petroules.com/support/kscemailtracker/"));
    ApplicationInfo::setUrl(ApplicationInfo::ApplicationUpdate, QUrl("https://www.petroules.com/version/kscemailtracker/"));
}

int main(int argc, char *argv[])
{
    QtSingleApplication instance("{DC8AF5C1-2488-4261-A882-AA52E98256E0}", argc, argv);
    Q_INIT_RESOURCE(globalresources);
    Q_INIT_RESOURCE(resources);

    // Set application version, copyright and other metadatas
    setAppInfo();
    ApplicationInfo::initialize(instance);

#ifdef Q_OS_WIN
    // We need this call to allow the original process to bring itself to the foreground
    AllowSetForegroundWindow(ASFW_ANY);
#endif

    // Send a string comprised of all but the first argument (the application name) to any other
    // instance that may be running, and bail out if it received it (e.g. it is running)
    QStringList args = instance.arguments();
    args.removeFirst();
    QString message = args.join(" ");
    if (instance.sendMessage(message))
    {
        return 0;
    }

    MainWindow *mw = new MainWindow();
    mw->show();
    mw->handleMessage(message);
    return instance.exec();
}
