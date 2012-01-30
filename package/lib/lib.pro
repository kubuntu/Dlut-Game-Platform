QT += xml
QT -= gui
TEMPLATE = lib
TARGET = dgppkg
VERSION = 0.0.1
CONFIG += create_prl

HEADERS += \
    src/packagemetainfo.h \
    src/zipobject.h \
    src/dgppkgreader.h \
    src/dgppkgwritter.h \
    src/dgppkgbase.h

SOURCES += \
    src/packagemetainfo.cpp \
    src/dgppkgreader.cpp \
    src/zipobject.cpp \
    src/dgppkgwritter.cpp \
    src/dgppkgbase.cpp

LIBS += -lzip
