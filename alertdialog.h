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
    TrackerSettings* m_settings;
    QMainWindow* m_trackerWindow;
    QList<MailMessageInfo*>* m_messages;
    void generateMarkup();
    void freeMessages();
};

#endif // ALERTDIALOG_H
