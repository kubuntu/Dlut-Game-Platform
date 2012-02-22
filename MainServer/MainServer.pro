QT -= gui
QT += network
TARGET = MainServer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
include(database/database.pri)
include(../api/api.pri)

HEADERS += \
    network/jmainserver.h \
    network/jmainserversocket.h \
    network/jmainserverloginprocessor.h \
    service/jloginverification.h \
    service/jmainserverinformationmanager.h \
    network/jmainserverinformationprocessor.h \
    service/jcommandmanager.h \
    network/jmainservercommandprocessor.h \
    service/jpermissioncontrol.h \
    service/jloginhashcodecreator.h \
    network/jmainserveruserregisterprocessor.h \
    service/juserregister.h \
    network/jmainserversocketstrategy.h \
    network/jmainservercontrolroleprocessor.h \
    service/jcontrolrole.h \
    service/juserstatemanager.h \
    network/jmainserverhalltalkprocessor.h \
    service/jhalltalkbroadcaster.h \
    network/jmainserverchangepasswordprocessor.h \
    service/jchangepassword.h
SOURCES += main/main.cpp \
	network/jmainserver.cpp \
    network/jmainserversocket.cpp \
    network/jmainserverloginprocessor.cpp \
    service/jloginverification.cpp \
    service/jmainserverinformationmanager.cpp \
    network/jmainserverinformationprocessor.cpp \
    service/jcommandmanager.cpp \
    network/jmainservercommandprocessor.cpp \
    service/jpermissioncontrol.cpp \
    service/jloginhashcodecreator.cpp \
    network/jmainserveruserregisterprocessor.cpp \
    service/juserregister.cpp \
    network/jmainserversocketstrategy.cpp \
    network/jmainservercontrolroleprocessor.cpp \
    service/jcontrolrole.cpp \
    service/juserstatemanager.cpp \
    network/jmainserverhalltalkprocessor.cpp \
    service/jhalltalkbroadcaster.cpp \
    network/jmainserverchangepasswordprocessor.cpp \
    service/jchangepassword.cpp
