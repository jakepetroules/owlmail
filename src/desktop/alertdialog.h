#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include <QtGui>
#include <QtWebKit>

class MailMessageInfo;
class TrackerPreferences;

namespace Ui
{
    class AlertDialog;
}

class AlertDialog : public QDialog
{
    Q_OBJECT

public:
    AlertDialog(QMainWindow* trackerWindow, QWidget* parent = NULL);
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
    QMainWindow* m_trackerWindow;
    QList<MailMessageInfo*>* m_messages;
    void generateMarkup();
    void freeMessages();
};

#endif // ALERTDIALOG_H
