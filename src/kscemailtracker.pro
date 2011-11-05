win32:TEMP_BUILDDIR = temp-win32-gcc
win32-msvc*:TEMP_BUILDDIR = temp-win32-msvc
macx:TEMP_BUILDDIR = temp-mac64
linux-g++:TEMP_BUILDDIR = temp-linux32

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    3rdparty/$$TEMP_BUILDDIR/synteza/qt \
    desktop
