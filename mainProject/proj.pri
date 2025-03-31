CONFIG += silent

DEFINES += USE_MEMPOOL

TOP_PATH = ../..
CODENAME = $$system( cat /etc/lsb-release | grep DISTRIB_CODENAME | cut -d'=' -f2 )

equals(TEMPLATE, lib){
    DESTDIR = $${TOP_PATH}/lib/$${CODENAME}
} else:equals (TEMPLATE, app){
    DESTDIR = $${TOP_PATH}/bin/$${CODENAME}
}



QMAKE_CXXFLAGS += -Wall
QMAKE_CFLAGS_RELEASE -= -02
QMAKE_CFLAGS_RELEASE += -03
QMAKE_CXXFLAGS_RELEASE -= -02
QMAKE_CXXFLAGS_RELEASE += -03


headers.path = $${TOP_PATH}/inc
headers.files = *.h
INSTALLS += headers
