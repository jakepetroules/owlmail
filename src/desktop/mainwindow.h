#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtNetwork>
#include <QtWebKit>
#include <integratedmainwindow.h>

class AlertDialog;
class TrackerPreferences;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public IntegratedMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = NULL);
    ~MainWindow();

public slots:
    void handleMessage(const QString &message);

signals:
    void needToShow();

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
    void help();
    void website();
    void donate();
    void checkForUpdates();
    void about();
    void browserReload();
    void browserLoaded(bool ok);
    void postponeButtonClicked(bool ok);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow* ui;
    QSystemTrayIcon* m_trayIcon;
    AlertDialog* m_alertDialog;
    QTimer* m_timer;
    QNetworkAccessManager* m_manager;
    QDateTime m_lastRefresh;
    int m_refreshInterval;

    inline void updateSingleInstance() { updateSingleInstance(this); }
    void updateSingleInstance(MainWindow *mw);
};

#endif // MAINWINDOW_H
