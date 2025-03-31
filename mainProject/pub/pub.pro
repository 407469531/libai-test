TEMPLATE = lib
CONFIG += staticlib
QT -= core gui
MYMODULE_NAME = pub

HEADERS += \
    pub.h

SOURCES += \
    pub.cpp

include(../proj.pri)

INCLUDEPATH +=

QMAKE_CLEAN += $${TOP_PATH}/lib/$${CODENAME}/libpub.a




