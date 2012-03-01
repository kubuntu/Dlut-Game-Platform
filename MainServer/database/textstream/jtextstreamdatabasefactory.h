#ifndef JTEXTSTREAMDATABASEFACTORY_H
#define JTEXTSTREAMDATABASEFACTORY_H

#include "../jabstractdatabasefactory.h"

class JTextStreamDatabaseFactory : public JAbstractDatabaseFactory
{
	explicit JTextStreamDatabaseFactory(QObject *parent = 0);
public:
	~JTextStreamDatabaseFactory();
	static JTextStreamDatabaseFactory* createInstance(QObject* parent);
	JAbstractLoginDB* createLoginDB();
	JAbstractUserInfoDB* createUserInfoDB();
	JAbstractGameInfoDB* createGameInfoDB();
	JAbstractServerInfoDB* createServerInfoDB();
	JAbstractInvitationCodeDB* createInvitationCodeDB();
};

#endif // JTEXTSTREAMDATABASEFACTORY_H
