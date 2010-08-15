include($$PWD/../common/petroules/qt/petroules-common.pri)

# We want Windows methods from at least Windows 2000 (NT 5.0)
win32:DEFINES += WINVER=0x0500

# -------------------------------------------------
# Include and build paths for external libraries
# -------------------------------------------------

LIEL_HEADERS = $$PWD/../liel/c++/liel
LIEL_BUILD = $$PWD/../liel/liel-build-desktop/lib
LIEL_LIB = liel
LIEL_VERSION = 1

QSA_HEADERS = $$PWD/../common/3rdparty/qtsingleapplication/src
QSA_BUILD = $$PWD/../common/3rdparty/qtsingleapplication/lib
QSA_LIB = qsa-2.6
