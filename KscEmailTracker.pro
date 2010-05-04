# -------------------------------------------------
# Project created by QtCreator 2010-01-27T22:20:37
# -------------------------------------------------
QT += network \
    webkit
TARGET = kscemailtracker
TEMPLATE = app
SOURCES += main.cpp \
    trackerwindow.cpp \
    trackersettings.cpp \
    mailmessageinfo.cpp \
    alertdialog.cpp \
    optionsdialog.cpp \
    aboutdialog.cpp
HEADERS += trackerwindow.h \
    trackersettings.h \
    mailmessageinfo.h \
    alertdialog.h \
    optionsdialog.h \
    version.h \
    aboutdialog.h
FORMS += trackerwindow.ui \
    alertdialog.ui \
    optionsdialog.ui
RESOURCES += resources.qrc

# General information
VERSION = 2.0.1

# Resource file for Windows
OTHER_FILES += kscemailtracker.rc
RC_FILE = kscemailtracker.rc

# Icon for Mac OS X application bundle
ICON = res/app.icns
