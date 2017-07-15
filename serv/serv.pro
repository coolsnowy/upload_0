TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    log.cpp \
    tcpserv.cpp \
    main.cpp \
    unpack.cpp \
    rsureg_unpack.cpp \
    map_unpakc.cpp \
    rsupart_unpack.cpp \
    rsucomm_unpack.cpp \
    spat_unpack.cpp \
    obureg_unpack.cpp \
    obubsm_unpack.cpp \
    obucomm_unpack.cpp

HEADERS += \
    log.h \
    tcpserv.h \
    unpack.h \
    data.h
