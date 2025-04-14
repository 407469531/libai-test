TEMPLATE = lib
CONFIG += staticlib
QT -= core gui
MYMODULE_NAME = pub

HEADERS += \
    memManage.h \
    memPool.h \
    objectPool.h \
    pub.h

SOURCES += \
    memManage.cpp \
    objectPool.cpp \
    pub.cpp

include(../proj.pri)

INCLUDEPATH +=

QMAKE_CLEAN += $${TOP_PATH}/lib/$${CODENAME}/libpub.a




