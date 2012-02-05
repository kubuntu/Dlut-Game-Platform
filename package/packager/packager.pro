QT -= gui
TARGET = dgp-packager
QMAKE_RPATHDIR += $$OUT_PWD/../lib/

HEADERS += \
    generatemetainfo.h \
    generatefilelist.h \
    jargumentanalysis.h
SOURCES += main.cpp \
    generatemetainfo.cpp \
    generatefilelist.cpp \
    jargumentanalysis.cpp

include(../lib/lib.pri)
