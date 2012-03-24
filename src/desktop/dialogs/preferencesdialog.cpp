#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "mailmessageinfo.h"
#include "trackerpreferences.h"

#define KEY_PATH "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define KEY_NAME "KSC Email Tracker"

/*!
    \class PreferencesDialog

    Represents an dialog allowing the user to set program options.
 */

/*!
    Constructs a new PreferencesDialog.
 */
PreferencesDialog::PreferencesDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog),
    m_idsRemoved(new QList<int>())
{
    this->ui->setupUi(this);

    // Update the password text box state depending on the state of the show password check box
    this->togglePassword(this->ui->showPasswordCheckBox->checkState());

    // Bring in the username and password from the settings
    this->ui->usernameTextBox->setText(TrackerPreferences::instance().username());
    this->ui->passwordTextBox->setText(TrackerPreferences::instance().password());

    // Bring in the messages for which alerts are suppressed
    for (int i = 0; i < TrackerPreferences::instance().suppressedMessages()->count(); i++)
    {
        this->ui->tableMessages->insertRow(i);
        this->ui->tableMessages->setCellWidget(i, 0, new QLabel(QString::number(TrackerPreferences::instance().suppressedMessages()->at(i)->id())));
        this->ui->tableMessages->setCellWidget(i, 1, new QLabel(TrackerPreferences::instance().suppressedMessages()->at(i)->subject()));
        this->ui->tableMessages->setCellWidget(i, 2, new QLabel(TrackerPreferences::instance().suppressedMessages()->at(i)->sender()));
        this->ui->tableMessages->setCellWidget(i, 3, new QLabel(TrackerPreferences::instance().suppressedMessages()->at(i)->received().toString("MM/dd/yyyy hh:mm AP")));
    }

#ifdef Q_OS_WIN32
    // If we're running on Windows, set the check box if the registry contains the correct key set to the running application's path
    QSettings reg(KEY_PATH, QSettings::NativeFormat);
    if (reg.contains(KEY_NAME) && reg.value(KEY_NAME).toString().compare(this->getApplicationFilePath(), Qt::CaseInsensitive))
    {
        this->ui->startWithWindowsCheckBox->setChecked(true);
    }
#else
    // Otherwise, disable and hide the start with Windows check box
    this->ui->startWithWindowsCheckBox->setEnabled(false);
    this->ui->startWithWindowsCheckBox->setVisible(false);
#endif
}

/*!
    Destroys the OptionsDialog.
 */
PreferencesDialog::~PreferencesDialog()
{
    delete this->ui;
    delete this->m_idsRemoved;
}

void PreferencesDialog::changeEvent(QEvent* e)
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

/*!
    Updates the registry depending on the state of the start with Windows check box.
 */
void PreferencesDialog::toggleStartup(int state)
{
    QSettings settings(KEY_PATH, QSettings::NativeFormat);
    if (state == Qt::Checked)
    {
        settings.setValue(KEY_NAME, "\"" + this->getApplicationFilePath() + "\"");
    }
    else if (state == Qt::Unchecked)
    {
        settings.remove(KEY_NAME);
    }
}

/*!
    Gets the file path of the currently running application.
 */
QString PreferencesDialog::getApplicationFilePath() const
{
    QString str = QApplication::applicationFilePath();
    #ifdef Q_OS_WIN32
    str.replace("/", "\\");
    #endif
    return str;
}

/*!
    Updates the echo mode (normal or password) of the password text box depending on the check state of the show password check box.
 */
void PreferencesDialog::togglePassword(int state)
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

/*!
    Removes the selected messages from the block list.
 */
void PreferencesDialog::removeSelected()
{
    // While we have messages selected...
    while (this->ui->tableMessages->selectedRanges().count() > 0)
    {
        // Get the index of the first row in the selection
        int row = this->ui->tableMessages->selectedRanges().at(0).topRow();

        // Append the specified message ID to the list of message IDs to unblock
        this->m_idsRemoved->append(((QLabel*)this->ui->tableMessages->cellWidget(row, 0))->text().toInt());

        // Remove the actual row from the table
        this->ui->tableMessages->removeRow(row);
    }
}

/*!
    Commits the current settings to disk.
 */
void PreferencesDialog::accept()
{
    // Commit the username and password to the settings
    TrackerPreferences::instance().setUsername(this->ui->usernameTextBox->text());
    TrackerPreferences::instance().setPassword(this->ui->passwordTextBox->text());

    // For any message IDs we wanted to unblock, remove them from the block list
    for (int i = 0; i < this->m_idsRemoved->count(); i++)
    {
        TrackerPreferences::instance().removeMessageWithId(this->m_idsRemoved->at(i));
    }

    #ifdef Q_OS_WIN32
    this->toggleStartup(this->ui->startWithWindowsCheckBox->checkState());
    #endif

    this->done(QDialog::Accepted);
}

/*!
    Cancels the dialog without saving any changed settings.
 */
void PreferencesDialog::reject()
{
    this->done(QDialog::Rejected);
}