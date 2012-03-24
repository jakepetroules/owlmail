#ifndef KSCEMAILTRACKERAPPLICATION_H
#define KSCEMAILTRACKERAPPLICATION_H

#include <petroules-utilities.h>

class KSCEmailTrackerApplication : public IntegratedApplication
{
    Q_OBJECT

public:
    explicit KSCEmailTrackerApplication(int &argc, char *argv[]);
    ~KSCEmailTrackerApplication();
    virtual bool handleReopen(bool hasVisibleWindows);

public slots:
    // Help menu
    void showHelpContents();
    void launchProductWebsite();
    void launchDonationsWebsite();

    // General (these go in separate menus in non-Mac platforms)
    void checkForUpdates();
    void checkForUpdatesSilent();
    void preferences();
    void about();

protected:
    bool event(QEvent *event);
    void showMainWindow();

private:
    class Private;
    Private *d;
};

#define qkApp (qobject_cast<KSCEmailTrackerApplication*>(qApp))

#endif // KSCEMAILTRACKERAPPLICATION_H
