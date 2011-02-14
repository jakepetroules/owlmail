# --------------------------------------------------
# This section contains project configuration
# directives such as the required Qt modules, the
# project template, and any variables that need to
# be defined.
# --------------------------------------------------

QT += network svg xml webkit
TEMPLATE = app
TARGET = kscemailtracker

# --------------------------------------------------
# This section contains all the main code/resource
# files that make up the target, including:
# * precompiled header (.pch)
# * headers (.h)
# * sources (.c, .cpp, .m, .mm, ...)
# * forms (.ui)
# * resources (.qrc)
# * translations (.tr)
# * any other files belonging in the OTHER_FILES var
# --------------------------------------------------

HEADERS += \
    mainwindow.h \
    trackerpreferences.h \
    mailmessageinfo.h \
    alertdialog.h \
    preferencesdialog.h \
    version.h \
    aboutdialog.h \
    licensedialog.h \
    updatedialog.h \
    trackerpreferences_keys.h
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    trackerpreferences.cpp \
    mailmessageinfo.cpp \
    alertdialog.cpp \
    preferencesdialog.cpp \
    aboutdialog.cpp \
    licensedialog.cpp \
    updatedialog.cpp
FORMS += \
    mainwindow.ui \
    alertdialog.ui \
    aboutdialog.ui \
    preferencesdialog.ui \
    licensedialog.ui \
    updatedialog.ui
RESOURCES += \
    resources.qrc \
    ../../res/globalresources.qrc
OTHER_FILES += \
    kscemailtracker.rc \
    version.pri \
    kscemailtracker.manifest \
    Info.plist

# --------------------------------------------------
# This section contains all libraries that the
# project links to, first system libraries, and then
# libraries in the project build tree.
# --------------------------------------------------

win32:LIBS += -luser32

!include(../3rdparty/temp/qtsolutions/qtsingleapplication/src/qtsingleapplication.pri) {
    error("Could not find the qtsingleapplication.pri file! Have you run configure in the 3rdparty directory?")
}

LIEL_PATH = ../3rdparty/temp/liel/qt/liel

# LIEL library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/$$LIEL_PATH/release/ -lliel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/$$LIEL_PATH/debug/ -lliel
else:symbian: LIBS += -lliel
else:unix: LIBS += -L$$OUT_PWD/$$LIEL_PATH/ -lliel

INCLUDEPATH += $$PWD/$$LIEL_PATH
DEPENDPATH += $$PWD/$$LIEL_PATH

macx:PRE_TARGETDEPS += $$OUT_PWD/$$LIEL_PATH/libliel.a

# --------------------------------------------------
# This section contains miscellaneous commands such
# as Windows resource files and icons for Mac OS X
# --------------------------------------------------

win32:RC_FILE = kscemailtracker.rc
macx:ICON = ../../res/app.icns
macx:QMAKE_INFO_PLIST = Info.plist

# Show the console when debugging on Windows
win32:CONFIG(debug, debug|release):CONFIG += console
