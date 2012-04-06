#ifndef OWLMAILAPPLICATION_H
#define OWLMAILAPPLICATION_H

#include <petroules-utilities.h>

class OwlMailApplication : public IntegratedApplication
{
    Q_OBJECT

public:
    explicit OwlMailApplication(int &argc, char *argv[]);
    ~OwlMailApplication();
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

#define qkApp (qobject_cast<OwlMailApplication*>(qApp))

#endif // OWLMAILAPPLICATION_H
