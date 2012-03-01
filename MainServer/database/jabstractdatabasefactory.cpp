#include "jabstractdatabasefactory.h"

#include "textstream/jtextstreamdatabasefactory.h"
#include "sql/jsqldatabasefactory.h"

#include <QSettings>

JAbstractDatabaseFactory* JAbstractDatabaseFactory::getInstance()
{
    static JAbstractDatabaseFactory* instance = NULL ;
    if( NULL == instance ){
        QString type = "sql";
        QSettings dgpdbIni ("dgpdb.ini", QSettings::IniFormat);
        type=dgpdbIni.value("type","sql").toString();
        
        static QObject parent ;
        if(type =="textstream"){
            instance = JTextStreamDatabaseFactory::createInstance(&parent);
        }else if(type == "sql"){
            instance = JSQLDatabaseFactory::createInstance(&parent);
        }
        
        if( NULL != instance ){
            instance->m_loginDB = instance->createLoginDB() ;
            instance->m_userInfoDB = instance->createUserInfoDB() ;
            instance->m_gameInfoDB = instance->createGameInfoDB() ;
            instance->m_serverInfoDB = instance->createServerInfoDB() ;
			instance->m_invitationCodeDB = instance->createInvitationCodeDB() ;
        }
    }
    return instance;
}

JAbstractLoginDB* JAbstractDatabaseFactory::getLoginDB(){
	return m_loginDB ;
}

JAbstractUserInfoDB* JAbstractDatabaseFactory::getUserInfoDB(){
	return m_userInfoDB ;
}

JAbstractGameInfoDB* JAbstractDatabaseFactory::getGameInfoDB(){
	return m_gameInfoDB ;
}

JAbstractServerInfoDB* JAbstractDatabaseFactory::getServerInfoDB(){
	return m_serverInfoDB ;
}

JAbstractInvitationCodeDB* JAbstractDatabaseFactory::getInvitationCodeDB(){
	return m_invitationCodeDB ;
}

JAbstractDatabaseFactory::JAbstractDatabaseFactory(QObject *parent)
	:QObject(parent)
{
}
