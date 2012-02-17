TARGET = MainClient
TEMPLATE = app
include(../api/api.pri)
include(../package/lib/lib.pri)
LIBS += -L../package/lib/
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../package/lib
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=lib/

SOURCES += main/main.cpp \
    gui/gamehall/mainwindow.cpp \
    gui/selectserver/jcomboselectserver.cpp \
    gui/login/jdlglogin.cpp \
    gui/selectserver/jdlgnewserver.cpp \
    gui/selectserver/shallserver.cpp \
    gui/login/settings/jrememberpassword.cpp \
    gui/login/settings/jsettinglogin.cpp \
    gui/selectserver/jdlgselectserver.cpp \
    gui/gamehall/jwidgetadmin.cpp \
    pseudoserver/jpseudoserver.cpp \
    pseudoserver/jpseudoserversocket.cpp \
    pseudoserver/jpseudoserverinformationprocessor.cpp \
    gui/login/jdialoguserregister.cpp \
    gui/gamehall/jdialogupdateuserinfo.cpp \
    service/jgameclientloader.cpp \
    service/jdownloader.cpp \
    gui/gamehall/jdialogstartgame.cpp \
    gui/gamehall/jwidgethalltalk.cpp \
    gui/gamehall/jformaddgame.cpp \
    service/jinstalledappmanager.cpp
HEADERS += gui/gamehall/mainwindow.h \
    gui/selectserver/jcomboselectserver.h \
    gui/login/jdlglogin.h \
    gui/selectserver/jdlgnewserver.h \
    gui/selectserver/shallserver.h \
    gui/login/settings/jrememberpassword.h \
    gui/login/settings/jsettinglogin.h \
    gui/selectserver/jdlgselectserver.h \
    gui/gamehall/jwidgetadmin.h \
    pseudoserver/jpseudoserver.h \
    pseudoserver/jpseudoserversocket.h \
    pseudoserver/jpseudoserverinformationprocessor.h \
    gui/login/jdialoguserregister.h \
    gui/gamehall/jdialogupdateuserinfo.h \
    service/jgameclientloader.h \
    service/jdownloader.h \
    gui/gamehall/jdialogstartgame.h \
    gui/gamehall/jwidgethalltalk.h \
    gui/gamehall/jformaddgame.h \
    service/jinstalledappmanager.h
FORMS += gui/gamehall/mainwindow.ui \
    gui/login/jdlglogin.ui \
    gui/selectserver/jdlgnewserver.ui \
    gui/selectserver/jdlgselectserver.ui \
    gui/gamehall/jwidgetadmin.ui \
    gui/login/jdialoguserregister.ui \
    gui/gamehall/jdialogupdateuserinfo.ui \
    gui/gamehall/jdialogstartgame.ui \
    gui/gamehall/jwidgethalltalk.ui \
    gui/gamehall/jformaddgame.ui
RESOURCES += \
    res/sources.qrc
