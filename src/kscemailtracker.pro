TEMPLATE = subdirs
CONFIG += ordered

win32-msvc* {
    TEMP_BUILDDIR = temp-win32-msvc
} else:win32 {
    TEMP_BUILDDIR = temp-win32-gcc
} else:macx {
    TEMP_BUILDDIR = temp-mac64
} else:linux-g++ {
    TEMP_BUILDDIR = temp-linux32
}

exists("3rdparty/$$TEMP_BUILDDIR/synteza/qt") {
    SUBDIRS += "3rdparty/$$TEMP_BUILDDIR/synteza/qt"
}

SUBDIRS += desktop
