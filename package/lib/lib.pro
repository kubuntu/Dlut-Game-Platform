QT += xml
QT -= gui
TEMPLATE = lib
TARGET = dgppkg
VERSION = 0.0.1

include(../../output.pri)

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
win32{
	INCLUDEPATH += C:/libzip/include
	LIBS += -LC:/libzip/lib
}
