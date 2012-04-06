!include(owlmail.pri):error(owlmail.pri is missing)

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += lib src

OTHER_FILES += README.md
