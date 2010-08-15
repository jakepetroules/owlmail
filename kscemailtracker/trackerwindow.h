#ifndef TRACKERWINDOW_H
#define TRACKERWINDOW_H

#include "alertdialog.h"
#include <trackersettings.h>
#include <QDateTime>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
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
    void beforeExit();
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
    void replyFinished(QNetworkReply* reply);

private:
    Ui::TrackerWindow* ui;
    TrackerSettings* m_settings;
    QSystemTrayIcon* m_trayIcon;
    AlertDialog* m_alertDialog;
    QTimer* m_timer;
    QNetworkAccessManager* m_manager;
    QDateTime m_lastRefresh;
    int m_refreshInterval;
};

#endif // TRACKERWINDOW_H
