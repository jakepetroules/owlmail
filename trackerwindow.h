#ifndef TRACKERWINDOW_H
#define TRACKERWINDOW_H

#include "alertdialog.h"
#include <trackersettings.h>
#include <QDateTime>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>

namespace Ui {
    class TrackerWindow;
}

class TrackerWindow : public QMainWindow {
    Q_OBJECT
public:
    TrackerWindow(QWidget *parent = 0);
    ~TrackerWindow();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    void initialize();
    void initializeTrayIcon();

protected slots:
    void exit();
    void navigateHome();
    void navigateInbox();
    void options();
    void checkForUpdates();
    void about();
    void browserReload();
    void browserLoaded(bool ok);
    void postponeButtonClicked(bool ok);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::TrackerWindow* ui;
    AlertDialog* alertDialog;
    QTimer* timer;
    QDateTime lastRefresh;
    int refreshInterval;
    QString kscPage;
    QString initialMailPage;
    QString mailPage;
    TrackerSettings* settings;
    QSystemTrayIcon* trayIcon;
};

#endif // TRACKERWINDOW_H
