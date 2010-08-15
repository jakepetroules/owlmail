#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QtGui>

class TrackerPreferences;

namespace Ui
{
    class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    PreferencesDialog(TrackerPreferences* settings, QWidget* parent = NULL);
    ~PreferencesDialog();

protected:
    void changeEvent(QEvent *e);
    void toggleStartup(int state);

protected slots:
    void togglePassword(int state);
    void removeSelected();
    void accept();
    void reject();

private:
    QString getApplicationFilePath() const;
    Ui::PreferencesDialog* ui;
    TrackerPreferences* m_settings;
    QList<int>* m_idsRemoved;
};

#endif // PREFERENCESDIALOG_H
