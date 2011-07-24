#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T10:40:24
#
#-------------------------------------------------
TARGET = clientapi
TEMPLATE = lib

include(../clientapi.pri)

DEFINES += CLIENTAPI_LIBRARY

SOURCES += \
		../src/network/jsocketbase.cpp \
		../src/service/jcryprorecorder.cpp \
		../src/service/jrequestlogin.cpp \
		../src/service/jrequestport.cpp \
		../src/network/jrequestloginsocket.cpp \
		../src/network/jrequestportsocket.cpp \
		../src/service/jrequestbase.cpp \
		../src/service/jplhrequestbase.cpp \
		../src/network/jplhsocketbase.cpp \
		../src/network/jrequestuserinfosocket.cpp \
		../src/service/jrequestuserinfo.cpp
HEADERS += \
		../include/network/jplhsocketbase.h \
		../include/network/jrequestloginsocket.h \
		../include/network/jrequestportsocket.h \
		../include/network/jrequestuserinfosocket.h \
		../include/network/jsocketbase.h \
		../include/service/jplhrequestbase.h \
		../include/service/jrequestbase.h
DESTDIR = ../lib
