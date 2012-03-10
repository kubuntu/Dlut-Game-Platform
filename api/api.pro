QT += network
TEMPLATE = lib
TARGET = dgpapi
VERSION = 0.1.1
CONFIG += create_prl

HEADERS += \
    src/network/jnetworkdataprocessorbase.h \
    src/network/jsocketbase.h \
    src/global/jglobal.h \
    src/network/jclientsocketbase.h \
    src/network/jserversocketbase.h \
    src/network/jclientnetworkdataprocessorbase.h \
    src/network/jclientloginprocessor.h \
    src/request/jrequestlogin.h \
    src/request/jrequestbase.h \
    src/global/elogin.h \
    src/global/shost.h \
    src/global/jinformation.h \
    src/network/jinformationmanager.h \
    src/global/jserializabledata.h \
    src/request/jrequestuserinfo.h \
    src/global/juserinfo.h \
    src/request/jinformationrequestbase.h \
    src/global/jgameinfo.h \
    src/request/jrequestgameinfo.h \
    src/global/jversion.h \
    src/global/jserverinfo.h \
    src/request/jrequestserverinfo.h \
    src/request/jinformationsendbase.h \
    src/request/juploadgameinfo.h \
    src/request/juploadserverinfo.h \
    src/network/jserverbase.h \
    src/network/jservernetworkdataprocessorbase.h \
    src/request/jinformationrequestbyheadbase.h \
    src/global/jgamelist.h \
    src/network/jclientinformationprocessor.h \
    src/network/jclientcommandprocessor.h \
    src/request/jsendcommand.h \
    src/global/command.h \
    src/global/jcodeerror.h \
    src/network/jsession.h \
    src/network/jserverinformationprocessorbase.h \
    src/network/jclientuserregisterprocessor.h \
    src/request/jrequestuserregister.h \
    src/global/eregister.h \
    src/network/jsocketstrategy.h \
    src/global/processor.h \
    src/network/jclientcontrolroleprocessor.h \
    src/request/jrequestcontrolrole.h \
    src/request/juploaduserinfo.h \
    src/request/jconnecthelper.h \
    src/network/jmainclientsocket.h \
    src/request/jgameserverstartup.h \
    src/network/jclienthalltalkprocessor.h \
    src/global/jencryptor.h \
    src/request/jgameclientargumentanalyser.h \
    src/global/jhead.h \
    src/network/jclientchangepasswordprocessor.h \
    src/request/juploadinvitationcode.h
SOURCES += src/network/jsocketbase.cpp \
    src/network/jclientsocketbase.cpp \
    src/network/jserversocketbase.cpp \
    src/network/jclientnetworkdataprocessorbase.cpp \
    src/network/jclientloginprocessor.cpp \
    src/request/jrequestlogin.cpp \
    src/request/jrequestbase.cpp \
    src/global/shost.cpp \
    src/global/jinformation.cpp \
    src/network/jinformationmanager.cpp \
    src/request/jrequestuserinfo.cpp \
    src/global/juserinfo.cpp \
    src/request/jinformationrequestbase.cpp \
    src/global/jgameinfo.cpp \
    src/request/jrequestgameinfo.cpp \
    src/global/jversion.cpp \
    src/global/jserverinfo.cpp \
    src/request/jrequestserverinfo.cpp \
    src/request/jinformationsendbase.cpp \
    src/request/juploadgameinfo.cpp \
    src/request/juploadserverinfo.cpp \
    src/global/jserializabledata.cpp \
    src/network/jserverbase.cpp \
    src/network/jservernetworkdataprocessorbase.cpp \
    src/request/jinformationrequestbyheadbase.cpp \
    src/global/jgamelist.cpp \
    src/network/jclientinformationprocessor.cpp \
    src/network/jclientcommandprocessor.cpp \
    src/request/jsendcommand.cpp \
    src/network/jsession.cpp \
    src/network/jserverinformationprocessorbase.cpp \
    src/network/jnetworkdataprocessorbase.cpp \
    src/network/jclientuserregisterprocessor.cpp \
    src/request/jrequestuserregister.cpp \
    src/network/jsocketstrategy.cpp \
    src/network/jclientcontrolroleprocessor.cpp \
    src/request/jrequestcontrolrole.cpp \
    src/request/juploaduserinfo.cpp \
    src/request/jconnecthelper.cpp \
    src/network/jmainclientsocket.cpp \
    src/request/jgameserverstartup.cpp \
    src/network/jclienthalltalkprocessor.cpp \
    src/global/jencryptor.cpp \
    src/request/jgameclientargumentanalyser.cpp \
    src/global/jhead.cpp \
    src/network/jclientchangepasswordprocessor.cpp \
    src/request/juploadinvitationcode.cpp
