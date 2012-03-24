TEMPLATE = subdirs
CONFIG += ordered

!exists(petroules-utilities-qt) {
    error("Please pull down the petroules-utilities-qt submodule using Git")
}

SUBDIRS += petroules-utilities-qt desktop
