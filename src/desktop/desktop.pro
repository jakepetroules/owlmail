# --------------------------------------------------
# This section contains project configuration
# directives such as the required Qt modules, the
# project template, and any variables that need to
# be defined.
# --------------------------------------------------

QT += network svg webkit xml
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
    kscemailtrackerapplication.h \
    mailmessageinfo.h \
    mainwindow.h \
    trackerpreferences.h \
    trackerpreferences_keys.h \
    version.h \
    dialogs/aboutdialog.h \
    dialogs/alertdialog.h \
    dialogs/licensedialog.h \
    dialogs/preferencesdialog.h \
    dialogs/updatedialog.h \
    trackerwebpage.h
SOURCES += \
    kscemailtrackerapplication.cpp \
    mailmessageinfo.cpp \
    main.cpp \
    mainwindow.cpp \
    trackerpreferences.cpp \
    dialogs/aboutdialog.cpp \
    dialogs/alertdialog.cpp \
    dialogs/licensedialog.cpp \
    dialogs/preferencesdialog.cpp \
    dialogs/updatedialog.cpp \
    trackerwebpage.cpp
FORMS += \
    mainwindow.ui \
    dialogs/aboutdialog.ui \
    dialogs/alertdialog.ui \
    dialogs/licensedialog.ui \
    dialogs/preferencesdialog.ui \
    dialogs/updatedialog.ui
RESOURCES += \
    resources.qrc \
    ../../res/globalresources.qrc
OTHER_FILES += \
    kscemailtracker.rc \
    kscemailtracker.manifest \
    Info.plist

# --------------------------------------------------
# This section contains all libraries that the
# project links to, first system libraries, and then
# libraries in the project build tree.
# --------------------------------------------------

win32:LIBS += -luser32
macx:LIBS += -framework Cocoa

PETROULESUTILITIES_PATH = ../petroules-utilities-qt/src
QTSOLUTIONS_PATH = $$PETROULESUTILITIES_PATH/../lib/qtsingleapplication/src

# Petroules Utilities library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/$$PETROULESUTILITIES_PATH/release/ -lpetroules-utilities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/$$PETROULESUTILITIES_PATH/debug/ -lpetroules-utilities
else:symbian: LIBS += -lpetroules-utilities
else:unix: LIBS += -L$$OUT_PWD/$$PETROULESUTILITIES_PATH/ -lpetroules-utilities

# We have to make sure we include the QtSingleApplication headers
# path because it will get indirectly included from THIS project
INCLUDEPATH += $$PWD/$$PETROULESUTILITIES_PATH $$PWD/$$QTSOLUTIONS_PATH
DEPENDPATH += $$PWD/$$PETROULESUTILITIES_PATH $$PWD/$$QTSOLUTIONS_PATH

macx:PRE_TARGETDEPS += $$OUT_PWD/$$PETROULESUTILITIES_PATH/libpetroules-utilities.a

# --------------------------------------------------
# This section contains miscellaneous commands such
# as Windows resource files and icons for Mac OS X
# --------------------------------------------------

win32:RC_FILE = kscemailtracker.rc
macx:ICON = ../../res/app.icns
macx:QMAKE_INFO_PLIST = Info.plist

# Show the console when debugging on Windows
win32:CONFIG(debug, debug|release):CONFIG += console

win32 {

    ## Windows common build here

    !contains(QMAKE_HOST.arch, x86_64) {
        message("x86 build")

        ## Windows x86 (32bit) specific build here

    } else {
        message("x86_64 build")

        ## Windows x64 (64bit) specific build here

    }
}
