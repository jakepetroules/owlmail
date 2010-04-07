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
    this->settings = settings;

    this->idsRemoved = new QList<int>();
    this->togglePassword(this->ui->showPasswordCheckBox->checkState());

    this->ui->usernameTextBox->setText(this->settings->getUsername());
    this->ui->passwordTextBox->setText(this->settings->getPassword());
    for (int i = 0; i < this->settings->getSuppressedMessages()->count(); i++)
    {
        this->ui->tableMessages->insertRow(i);
        this->ui->tableMessages->setCellWidget(i, 0, new QLabel(QString::number(this->settings->getSuppressedMessages()->at(i)->getId())));
        this->ui->tableMessages->setCellWidget(i, 1, new QLabel(this->settings->getSuppressedMessages()->at(i)->getSubject()));
        this->ui->tableMessages->setCellWidget(i, 2, new QLabel(this->settings->getSuppressedMessages()->at(i)->getSender()));
        this->ui->tableMessages->setCellWidget(i, 3, new QLabel(this->settings->getSuppressedMessages()->at(i)->getReceived().toString("MM/dd/yyyy hh:mm AP")));
    }

    #ifdef Q_OS_WIN32
    QSettings reg("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (reg.contains("KSC Email Tracker"))
    {
        this->ui->startWithWindowsCheckBox->setChecked(true);
    }
    #else
    this->ui->startWithWindowsCheckBox->setVisible(false);
    #endif
}

OptionsDialog::~OptionsDialog()
{
    delete this->ui;
    delete this->idsRemoved;
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
    while (this->ui->tableMessages->selectedRanges().count() > 0)
    {
        int row = this->ui->tableMessages->selectedRanges().at(0).topRow();
        this->idsRemoved->append(((QLabel*)this->ui->tableMessages->cellWidget(row, 0))->text().toInt());
        this->ui->tableMessages->removeRow(row);
    }
}

void OptionsDialog::accept()
{
    // Commit the username and password to the settings
    this->settings->setUsername(this->ui->usernameTextBox->text());
    this->settings->setPassword(this->ui->passwordTextBox->text());

    for (int i = 0; i < this->idsRemoved->count(); i++)
    {
        this->settings->removeMessageWithId(this->idsRemoved->at(i));
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
