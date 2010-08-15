# -------------------------------------------------
# Project created by QtCreator 2010-01-27T22:20:37
# -------------------------------------------------
include(../common.pri)
include(version.pri)

QT += network \
    webkit
TARGET = $$APP_UNIXNAME
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    trackerpreferences.cpp \
    mailmessageinfo.cpp \
    alertdialog.cpp \
    preferencesdialog.cpp \
    aboutdialog.cpp licensedialog.cpp
HEADERS += mainwindow.h \
    trackerpreferences.h \
    mailmessageinfo.h \
    alertdialog.h \
    preferencesdialog.h \
    version.h \
    aboutdialog.h licensedialog.h
FORMS += mainwindow.ui \
    alertdialog.ui \
    aboutdialog.ui \
    preferencesdialog.ui licensedialog.ui
RESOURCES += resources.qrc ../res/globalresources.qrc
DESTDIR = ../bin
INCLUDEPATH += $$LIEL_HEADERS $$QSA_HEADERS
LIBS += -L$$LIEL_BUILD -l$$platformversion($$LIEL_LIB, $$LIEL_VERSION) -L$$QSA_BUILD -l$$QSA_LIB
OTHER_FILES += kscemailtracker.rc \
    version.pri kscemailtracker.manifest Info.plist

# Copy over dependent libraries - not necessary on Mac OS X as macdeployqt will take care of it...
!macx {
    QMAKE_POST_LINK += $$COPY_CMD $$formatpath($$LIEL_BUILD/*.$$LIB_EXT) $$formatpath($$OUT_PWD/$$DESTDIR) $$CMD_SEP
    QMAKE_POST_LINK += $$COPY_CMD $$formatpath($$QSA_BUILD/*.$$LIB_EXT) $$formatpath($$OUT_PWD/$$DESTDIR) $$CMD_SEP
}

win32 {
    RC_FILE = kscemailtracker.rc
}

macx {
    ICON = res/app.icns

    # Use our custom plist file and populate it with the correct information
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_POST_LINK += $$populateplist()

    # Run macdeployqt and rename the bundle to its friendly name
    QMAKE_POST_LINK += $$macdeployqt(3) $$renamebundle()
}

linux-g++ {
    # Copy launcher shell script and make executable
    QMAKE_POST_LINK += $$COPY_CMD $$formatpath($$PWD/../deploy/linux/launcher.sh) $$formatpath($$OUT_PWD/$$DESTDIR/$${TARGET}.sh) $$CMD_SEP
    QMAKE_POST_LINK += chmod +x $$formatpath($${OUT_PWD}/$${DESTDIR}/$${TARGET}.sh) $$CMD_SEP

    # Copy desktop entry file
    QMAKE_POST_LINK += $$COPY_CMD $$formatpath($$PWD/../deploy/linux/launcher.desktop) $$formatpath($$OUT_PWD/$$DESTDIR/$${TARGET}.desktop) $$CMD_SEP

    # Copy application icon
    QMAKE_POST_LINK += $$COPY_CMD $$formatpath($$PWD/res/app.svg) $$formatpath($$OUT_PWD/$$DESTDIR) $$CMD_SEP
}
