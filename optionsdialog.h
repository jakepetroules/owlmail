#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include "trackersettings.h"

namespace Ui {
    class OptionsDialog;
}

class OptionsDialog : public QDialog {
    Q_OBJECT
public:
    OptionsDialog(TrackerSettings* settings, QWidget* parent = 0);
    ~OptionsDialog();

protected:
    void changeEvent(QEvent *e);
    void toggleStartup(int state);

protected slots:
    void togglePassword(int state);
    void removeSelected();
    void accept();
    void reject();

private:
    Ui::OptionsDialog *ui;
    TrackerSettings* settings;
};

#endif // OPTIONSDIALOG_H
