#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "trackersettings.h"
#include <QMessageBox>
#include <QSettings>

OptionsDialog::OptionsDialog(TrackerSettings* settings, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    this->ui->setupUi(this);
    this->togglePassword(QLineEdit::Password);

    this->settings = settings;
    this->ui->usernameTextBox->setText(this->settings->getUsername());
    this->ui->passwordTextBox->setText(this->settings->getPassword());
    for (int i = 0; i < this->settings->getSuppressedMessages()->count(); i++)
    {
        this->ui->tableMessages->insertRow(i);
        this->ui->tableMessages->setCellWidget(i, 0, new QLabel(QString::number(this->settings->getSuppressedMessages()->at(i))));
        this->ui->tableMessages->setCellWidget(i, 1, new QLabel(""));
    }

    #ifdef Q_OS_WIN32
    QSettings reg("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (reg.contains("KSC Email Tracker"))
    {
        this->ui->startWithWindowsCheckBox->setChecked(true);
    }
    #else
    this->ui->startWithWindowsCheckBox->setEnabled(false);
    #endif
}

OptionsDialog::~OptionsDialog()
{
    delete this->ui;
}

void OptionsDialog::changeEvent(QEvent* e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            this->ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void OptionsDialog::toggleStartup(int state)
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (state == Qt::Checked)
    {
        settings.setValue("KSC Email Tracker", "\"" + QApplication::applicationFilePath() + "\"");
    }
    else if (state == Qt::Unchecked)
    {
        settings.remove("KSC Email Tracker");
    }
}

void OptionsDialog::togglePassword(int state)
{
    if (state == Qt::Checked)
    {
        this->ui->passwordTextBox->setEchoMode(QLineEdit::Normal);
    }
    else if (state == Qt::Unchecked)
    {
        this->ui->passwordTextBox->setEchoMode(QLineEdit::Password);
    }
}

void OptionsDialog::removeSelected()
{
    /*QModelIndexList indexes = this->ui->tableMessages->selectedIndexes();
    while (indexes.count() > 0)
    {
        this->ui->tableMessages->removeRow(indexes.at(0));
        indexes = this->ui->tableMessages->selectedIndexes();
    }*/
}

void OptionsDialog::accept()
{
    // Commit the username and password to the settings
    this->settings->setUsername(this->ui->usernameTextBox->text());
    this->settings->setPassword(this->ui->passwordTextBox->text());

    // Clear the currently suppressed messages
    QList<int>* messages = this->settings->getSuppressedMessages();
    messages->clear();

    // Then add all the ones in the options dialog
    for (int i = 0; i < this->ui->tableMessages->rowCount(); i++)
    {
        QLabel* widget = (QLabel*)this->ui->tableMessages->cellWidget(i, 0);
        messages->append(widget->text().toInt());
    }

    #ifdef Q_OS_WIN32
    this->toggleStartup(this->ui->startWithWindowsCheckBox->checkState());
    #endif

    this->done(QDialog::Accepted);
}

void OptionsDialog::reject()
{
    this->done(QDialog::Rejected);
}
