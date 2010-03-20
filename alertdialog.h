#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include "mailmessageinfo.h"
#include <QDialog>
#include <QList>
#include <QUrl>

namespace Ui {
    class AlertDialog;
}

class AlertDialog : public QDialog {
    Q_OBJECT
public:
    AlertDialog(QWidget *parent = 0);
    ~AlertDialog();
    QList<MailMessageInfo>* suppressedMessages();
    void show(QList<MailMessageInfo>* messages);
    void show();
    void snapToCorner();

protected:
    void changeEvent(QEvent *e);

protected slots:
    void loadFinished(bool);
    void linkClicked(QUrl);

private:
    Ui::AlertDialog *ui;
    void generateMarkup(QList<MailMessageInfo>* messages);
};

#endif // ALERTDIALOG_H
