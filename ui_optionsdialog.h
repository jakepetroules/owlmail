/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created: Sun Apr 4 02:28:43 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *usernameLabel;
    QLineEdit *usernameTextBox;
    QLineEdit *passwordTextBox;
    QLabel *passwordLabel;
    QTableWidget *tableMessages;
    QLabel *messagesLabel;
    QPushButton *buttonRemoveSelected;
    QCheckBox *showPasswordCheckBox;
    QCheckBox *startWithWindowsCheckBox;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QString::fromUtf8("OptionsDialog"));
        OptionsDialog->resize(500, 306);
        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 270, 481, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        usernameLabel = new QLabel(OptionsDialog);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        usernameLabel->setGeometry(QRect(10, 10, 51, 21));
        usernameTextBox = new QLineEdit(OptionsDialog);
        usernameTextBox->setObjectName(QString::fromUtf8("usernameTextBox"));
        usernameTextBox->setGeometry(QRect(70, 10, 113, 20));
        passwordTextBox = new QLineEdit(OptionsDialog);
        passwordTextBox->setObjectName(QString::fromUtf8("passwordTextBox"));
        passwordTextBox->setGeometry(QRect(70, 40, 113, 20));
        passwordLabel = new QLabel(OptionsDialog);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setGeometry(QRect(10, 40, 51, 21));
        tableMessages = new QTableWidget(OptionsDialog);
        if (tableMessages->columnCount() < 2)
            tableMessages->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableMessages->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableMessages->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableMessages->setObjectName(QString::fromUtf8("tableMessages"));
        tableMessages->setGeometry(QRect(180, 70, 311, 192));
        messagesLabel = new QLabel(OptionsDialog);
        messagesLabel->setObjectName(QString::fromUtf8("messagesLabel"));
        messagesLabel->setGeometry(QRect(10, 70, 161, 21));
        buttonRemoveSelected = new QPushButton(OptionsDialog);
        buttonRemoveSelected->setObjectName(QString::fromUtf8("buttonRemoveSelected"));
        buttonRemoveSelected->setGeometry(QRect(74, 100, 101, 23));
        showPasswordCheckBox = new QCheckBox(OptionsDialog);
        showPasswordCheckBox->setObjectName(QString::fromUtf8("showPasswordCheckBox"));
        showPasswordCheckBox->setGeometry(QRect(190, 40, 101, 21));
        startWithWindowsCheckBox = new QCheckBox(OptionsDialog);
        startWithWindowsCheckBox->setObjectName(QString::fromUtf8("startWithWindowsCheckBox"));
        startWithWindowsCheckBox->setGeometry(QRect(370, 10, 121, 21));

        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));
        QObject::connect(buttonRemoveSelected, SIGNAL(clicked()), OptionsDialog, SLOT(removeSelected()));
        QObject::connect(showPasswordCheckBox, SIGNAL(stateChanged(int)), OptionsDialog, SLOT(togglePassword(int)));

        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        usernameLabel->setText(QApplication::translate("OptionsDialog", "Username:", 0, QApplication::UnicodeUTF8));
        passwordLabel->setText(QApplication::translate("OptionsDialog", "Password:", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableMessages->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("OptionsDialog", "Message ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableMessages->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("OptionsDialog", "Message Subject", 0, QApplication::UnicodeUTF8));
        messagesLabel->setText(QApplication::translate("OptionsDialog", "Messages NOT to show alerts on:", 0, QApplication::UnicodeUTF8));
        buttonRemoveSelected->setText(QApplication::translate("OptionsDialog", "Remove selected", 0, QApplication::UnicodeUTF8));
        showPasswordCheckBox->setText(QApplication::translate("OptionsDialog", "Show password", 0, QApplication::UnicodeUTF8));
        startWithWindowsCheckBox->setText(QApplication::translate("OptionsDialog", "Start with Windows", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
