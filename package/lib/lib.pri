INCLUDEPATH += $$PWD/include
LIBS += -L../lib/ -ldgppkg
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../lib
CONFIG += use_prl
QT += xml
LIBS += -lzip
