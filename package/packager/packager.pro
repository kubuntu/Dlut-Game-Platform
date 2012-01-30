QT -= gui
TARGET = dgp-packager
QMAKE_RPATHDIR += $$OUT_PWD/../lib/

HEADERS += \
    generatemetainfo.h \
    generatefilelist.h
SOURCES += main.cpp \
    generatemetainfo.cpp \
    generatefilelist.cpp

include(../lib/lib.pri)


