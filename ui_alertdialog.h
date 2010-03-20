/********************************************************************************
** Form generated from reading UI file 'alertdialog.ui'
**
** Created: Fri Jan 29 21:00:08 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERTDIALOG_H
#define UI_ALERTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_AlertDialog
{
public:
    QGridLayout *gridLayout;
    QWebView *webView;

    void setupUi(QDialog *AlertDialog)
    {
        if (AlertDialog->objectName().isEmpty())
            AlertDialog->setObjectName(QString::fromUtf8("AlertDialog"));
        AlertDialog->resize(600, 16);
        gridLayout = new QGridLayout(AlertDialog);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webView = new QWebView(AlertDialog);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl("about:blank"));

        gridLayout->addWidget(webView, 0, 0, 1, 1);


        retranslateUi(AlertDialog);
        QObject::connect(webView, SIGNAL(loadFinished(bool)), AlertDialog, SLOT(loadFinished(bool)));
        QObject::connect(webView, SIGNAL(linkClicked(QUrl)), AlertDialog, SLOT(linkClicked(QUrl)));

        QMetaObject::connectSlotsByName(AlertDialog);
    } // setupUi

    void retranslateUi(QDialog *AlertDialog)
    {
        AlertDialog->setWindowTitle(QApplication::translate("AlertDialog", "New MyKSC Email Messages", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AlertDialog: public Ui_AlertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERTDIALOG_H
