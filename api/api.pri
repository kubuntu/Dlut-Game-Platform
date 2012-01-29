INCLUDEPATH += $$PWD/include
LIBS += -L../api/ -ldgpapi
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../api
CONFIG += use_prl
QT += network
