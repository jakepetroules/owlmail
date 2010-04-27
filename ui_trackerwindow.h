/********************************************************************************
** Form generated from reading UI file 'trackerwindow.ui'
**
** Created: Mon Apr 26 16:57:00 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKERWINDOW_H
#define UI_TRACKERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_TrackerWindow
{
public:
    QAction *actionE_xit;
    QAction *actionAbout;
    QAction *actionCheck_for_Updates;
    QAction *actionOptions;
    QAction *actionMyKSC_Home;
    QAction *actionMyKSC_Inbox;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWebView *webView;
    QGridLayout *gridLayout_2;
    QPushButton *postponeButton;
    QLabel *timeLabel;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuHelp;
    QMenu *menu_Tools;
    QMenu *menuNavigate;

    void setupUi(QMainWindow *TrackerWindow)
    {
        if (TrackerWindow->objectName().isEmpty())
            TrackerWindow->setObjectName(QString::fromUtf8("TrackerWindow"));
        TrackerWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/res/app.png"), QSize(), QIcon::Normal, QIcon::Off);
        TrackerWindow->setWindowIcon(icon);
        actionE_xit = new QAction(TrackerWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        actionAbout = new QAction(TrackerWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionCheck_for_Updates = new QAction(TrackerWindow);
        actionCheck_for_Updates->setObjectName(QString::fromUtf8("actionCheck_for_Updates"));
        actionOptions = new QAction(TrackerWindow);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionMyKSC_Home = new QAction(TrackerWindow);
        actionMyKSC_Home->setObjectName(QString::fromUtf8("actionMyKSC_Home"));
        actionMyKSC_Inbox = new QAction(TrackerWindow);
        actionMyKSC_Inbox->setObjectName(QString::fromUtf8("actionMyKSC_Inbox"));
        centralWidget = new QWidget(TrackerWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webView = new QWebView(centralWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy);
        webView->setUrl(QUrl("about:blank"));

        gridLayout->addWidget(webView, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, -1, -1, 8);
        postponeButton = new QPushButton(centralWidget);
        postponeButton->setObjectName(QString::fromUtf8("postponeButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(postponeButton->sizePolicy().hasHeightForWidth());
        postponeButton->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(postponeButton, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 2, 0, 4, 1);

        timeLabel = new QLabel(centralWidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(timeLabel, 1, 0, 1, 1);

        TrackerWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TrackerWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menuNavigate = new QMenu(menuBar);
        menuNavigate->setObjectName(QString::fromUtf8("menuNavigate"));
        TrackerWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuNavigate->menuAction());
        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu_File->addAction(actionE_xit);
        menuHelp->addAction(actionAbout);
        menu_Tools->addAction(actionOptions);
        menu_Tools->addSeparator();
        menu_Tools->addAction(actionCheck_for_Updates);
        menuNavigate->addAction(actionMyKSC_Home);
        menuNavigate->addAction(actionMyKSC_Inbox);

        retranslateUi(TrackerWindow);
        QObject::connect(actionE_xit, SIGNAL(triggered()), TrackerWindow, SLOT(exit()));
        QObject::connect(actionOptions, SIGNAL(triggered()), TrackerWindow, SLOT(options()));
        QObject::connect(actionCheck_for_Updates, SIGNAL(triggered()), TrackerWindow, SLOT(checkForUpdates()));
        QObject::connect(actionAbout, SIGNAL(triggered()), TrackerWindow, SLOT(about()));
        QObject::connect(webView, SIGNAL(loadFinished(bool)), TrackerWindow, SLOT(browserLoaded(bool)));
        QObject::connect(actionMyKSC_Home, SIGNAL(triggered()), TrackerWindow, SLOT(navigateHome()));
        QObject::connect(actionMyKSC_Inbox, SIGNAL(triggered()), TrackerWindow, SLOT(navigateInbox()));
        QObject::connect(TrackerWindow, SIGNAL(destroyed()), TrackerWindow, SLOT(exit()));
        QObject::connect(postponeButton, SIGNAL(clicked(bool)), TrackerWindow, SLOT(postponeButtonClicked(bool)));

        QMetaObject::connectSlotsByName(TrackerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TrackerWindow)
    {
        TrackerWindow->setWindowTitle(QApplication::translate("TrackerWindow", "KSC Email Tracker", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("TrackerWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("TrackerWindow", "About", 0, QApplication::UnicodeUTF8));
        actionCheck_for_Updates->setText(QApplication::translate("TrackerWindow", "Check for Updates", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("TrackerWindow", "&Options...", 0, QApplication::UnicodeUTF8));
        actionMyKSC_Home->setText(QApplication::translate("TrackerWindow", "MyKSC Home", 0, QApplication::UnicodeUTF8));
        actionMyKSC_Inbox->setText(QApplication::translate("TrackerWindow", "MyKSC Inbox", 0, QApplication::UnicodeUTF8));
        postponeButton->setText(QApplication::translate("TrackerWindow", "Postpone", 0, QApplication::UnicodeUTF8));
        timeLabel->setText(QApplication::translate("TrackerWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("TrackerWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("TrackerWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menu_Tools->setTitle(QApplication::translate("TrackerWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menuNavigate->setTitle(QApplication::translate("TrackerWindow", "Navigate", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrackerWindow: public Ui_TrackerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKERWINDOW_H
