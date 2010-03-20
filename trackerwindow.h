#ifndef TRACKERWINDOW_H
#define TRACKERWINDOW_H

#include "alertdialog.h"
#include <QDateTime>
#include <QMainWindow>
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
    void initialize();

protected slots:
    void exit();
    void navigateHome();
    void navigateInbox();
    void options();
    void checkForUpdates();
    void about();
    void browserReload();
    void browserLoaded(bool ok);

private:
    Ui::TrackerWindow *ui;
    AlertDialog* alertDialog;
    QTimer* timer;
    QDateTime lastRefresh;
    int refreshInterval;
    QString kscPage;
    QString mailPage;
};

#endif // TRACKERWINDOW_H
