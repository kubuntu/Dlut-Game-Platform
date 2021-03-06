#ifndef JABSTRACTDATABASEFACTORY_H
#define JABSTRACTDATABASEFACTORY_H

#include <QObject>

#include "jabstractlogindb.h"
#include "jabstractuserinfodb.h"
#include "jabstractgameinfodb.h"
#include "jabstractserverinfodb.h"
#include "jabstractinvitationcodedb.h"

class JAbstractDatabaseFactory : public QObject
{
protected:
	explicit JAbstractDatabaseFactory(QObject *parent = 0);
public:
	static JAbstractDatabaseFactory* getInstance();
	JAbstractLoginDB* getLoginDB();
	JAbstractUserInfoDB* getUserInfoDB();
	JAbstractGameInfoDB* getGameInfoDB();
	JAbstractServerInfoDB* getServerInfoDB();
	JAbstractInvitationCodeDB* getInvitationCodeDB() ;
protected:
	virtual JAbstractLoginDB* createLoginDB()=0;
	virtual JAbstractUserInfoDB* createUserInfoDB()=0;
	virtual JAbstractGameInfoDB* createGameInfoDB()=0;
	virtual JAbstractServerInfoDB* createServerInfoDB()=0;
	virtual JAbstractInvitationCodeDB* createInvitationCodeDB()=0;
private:
	JAbstractLoginDB* m_loginDB;
	JAbstractUserInfoDB* m_userInfoDB;
	JAbstractGameInfoDB* m_gameInfoDB;
	JAbstractServerInfoDB* m_serverInfoDB;
	JAbstractInvitationCodeDB* m_invitationCodeDB ;
};

#endif // JABSTRACTDATABASEFACTORY_H
