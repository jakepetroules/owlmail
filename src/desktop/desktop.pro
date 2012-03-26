!include(../../kscemailtracker.pri):error(../../kscemailtracker.pri is missing)

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
    $${TARGET}.rc \
    $${TARGET}.manifest \
    Info.plist

# --------------------------------------------------
# Destination directory and build configuration
# --------------------------------------------------

DESTDIR = $$OUT_PWD/../../bin

CONFIG(release, debug|release):DESTDIR = $$DESTDIR/release
else:CONFIG(debug, debug|release):DESTDIR = $$DESTDIR/debug

# --------------------------------------------------
# This section contains all libraries that the
# project links to, first system libraries, and then
# libraries in the project build tree.
# --------------------------------------------------

win32:LIBS += -luser32
macx:LIBS += -framework Cocoa

# Petroules Utilities library
includeLib(../../lib/petroules-utilities-qt/src, petroules-utilities, static)

# OpenSSL
win32:QMAKE_PRE_LINK += $$QMAKE_COPY $$formatpath($$PWD/../../lib/openssl-win32/*.dll) $$formatpath($$DESTDIR)

# --------------------------------------------------
# This section contains miscellaneous commands such
# as Windows resource files and icons for Mac OS X
# --------------------------------------------------

win32:RC_FILE = $${TARGET}.rc
macx:ICON = ../../res/app.icns
macx:QMAKE_INFO_PLIST = Info.plist

# Show the console when debugging on Windows
win32:CONFIG(debug, debug|release):CONFIG += console

!contains(QMAKE_HOST.arch, x86_64) {
    !build_pass:message("x86 build")
} else {
    !build_pass:message("x86_64 build")
}
