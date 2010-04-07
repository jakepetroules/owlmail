#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include "mailmessageinfo.h"
#include "trackersettings.h"
#include <QDialog>
#include <QList>
#include <QMainWindow>
#include <QUrl>

namespace Ui {
    class AlertDialog;
}

class AlertDialog : public QDialog {
    Q_OBJECT
public:
    AlertDialog(TrackerSettings* settings, QMainWindow* trackerWindow, QWidget* parent = 0);
    ~AlertDialog();
    void show(QList<MailMessageInfo*>* messages);
    void show();
    void snapToCorner();

protected:
    void changeEvent(QEvent *e);

protected slots:
    void loadFinished(bool);
    void linkClicked(QUrl);

private:
    Ui::AlertDialog* ui;
    TrackerSettings* settings;
    QMainWindow* trackerWindow;
    QList<MailMessageInfo*>* messages;
    void generateMarkup();
};

#endif // ALERTDIALOG_H
