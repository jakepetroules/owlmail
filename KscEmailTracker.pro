# -------------------------------------------------
# Project created by QtCreator 2010-01-27T22:20:37
# -------------------------------------------------
QT += network \
    webkit
TARGET = KscEmailTracker
TEMPLATE = app
SOURCES += main.cpp \
    trackerwindow.cpp \
    trackersettings.cpp \
    mailmessageinfo.cpp \
    alertdialog.cpp \
    optionsdialog.cpp
HEADERS += trackerwindow.h \
    trackersettings.h \
    mailmessageinfo.h \
    alertdialog.h \
    optionsdialog.h
FORMS += trackerwindow.ui \
    alertdialog.ui \
    optionsdialog.ui
RESOURCES += resources.qrc
OTHER_FILES += kscemailtracker.rc
RC_FILE = kscemailtracker.rc
ICON = res/app.icns
