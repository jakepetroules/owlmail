/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created: Mon Apr 26 16:57:00 2010
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
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameTextBox;
    QLabel *passwordLabel;
    QLineEdit *passwordTextBox;
    QCheckBox *showPasswordCheckBox;
    QLabel *messagesLabel;
    QTableWidget *tableMessages;
    QDialogButtonBox *buttonBox;
    QCheckBox *startWithWindowsCheckBox;
    QPushButton *buttonRemoveSelected;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QString::fromUtf8("OptionsDialog"));
        OptionsDialog->resize(500, 306);
        formLayout = new QFormLayout(OptionsDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        usernameLabel = new QLabel(OptionsDialog);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        usernameTextBox = new QLineEdit(OptionsDialog);
        usernameTextBox->setObjectName(QString::fromUtf8("usernameTextBox"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(usernameTextBox->sizePolicy().hasHeightForWidth());
        usernameTextBox->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::FieldRole, usernameTextBox);

        passwordLabel = new QLabel(OptionsDialog);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, passwordLabel);

        passwordTextBox = new QLineEdit(OptionsDialog);
        passwordTextBox->setObjectName(QString::fromUtf8("passwordTextBox"));
        sizePolicy.setHeightForWidth(passwordTextBox->sizePolicy().hasHeightForWidth());
        passwordTextBox->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::FieldRole, passwordTextBox);

        showPasswordCheckBox = new QCheckBox(OptionsDialog);
        showPasswordCheckBox->setObjectName(QString::fromUtf8("showPasswordCheckBox"));

        formLayout->setWidget(3, QFormLayout::FieldRole, showPasswordCheckBox);

        messagesLabel = new QLabel(OptionsDialog);
        messagesLabel->setObjectName(QString::fromUtf8("messagesLabel"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, messagesLabel);

        tableMessages = new QTableWidget(OptionsDialog);
        if (tableMessages->columnCount() < 4)
            tableMessages->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableMessages->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableMessages->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableMessages->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableMessages->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableMessages->setObjectName(QString::fromUtf8("tableMessages"));
        tableMessages->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableMessages->setDragDropMode(QAbstractItemView::NoDragDrop);
        tableMessages->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableMessages->setSortingEnabled(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, tableMessages);

        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(8, QFormLayout::SpanningRole, buttonBox);

        startWithWindowsCheckBox = new QCheckBox(OptionsDialog);
        startWithWindowsCheckBox->setObjectName(QString::fromUtf8("startWithWindowsCheckBox"));

        formLayout->setWidget(7, QFormLayout::LabelRole, startWithWindowsCheckBox);

        buttonRemoveSelected = new QPushButton(OptionsDialog);
        buttonRemoveSelected->setObjectName(QString::fromUtf8("buttonRemoveSelected"));

        formLayout->setWidget(5, QFormLayout::LabelRole, buttonRemoveSelected);


        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));
        QObject::connect(buttonRemoveSelected, SIGNAL(clicked()), OptionsDialog, SLOT(removeSelected()));
        QObject::connect(showPasswordCheckBox, SIGNAL(stateChanged(int)), OptionsDialog, SLOT(togglePassword(int)));

        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Options", 0, QApplication::UnicodeUTF8));
        usernameLabel->setText(QApplication::translate("OptionsDialog", "Username:", 0, QApplication::UnicodeUTF8));
        passwordLabel->setText(QApplication::translate("OptionsDialog", "Password:", 0, QApplication::UnicodeUTF8));
        showPasswordCheckBox->setText(QApplication::translate("OptionsDialog", "Show password", 0, QApplication::UnicodeUTF8));
        messagesLabel->setText(QApplication::translate("OptionsDialog", "Messages NOT to show alerts on:", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableMessages->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("OptionsDialog", "Message ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableMessages->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("OptionsDialog", "Subject", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableMessages->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("OptionsDialog", "Sender", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableMessages->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("OptionsDialog", "Date/Time Received", 0, QApplication::UnicodeUTF8));
        startWithWindowsCheckBox->setText(QApplication::translate("OptionsDialog", "Start with Windows", 0, QApplication::UnicodeUTF8));
        buttonRemoveSelected->setText(QApplication::translate("OptionsDialog", "Remove selected", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
