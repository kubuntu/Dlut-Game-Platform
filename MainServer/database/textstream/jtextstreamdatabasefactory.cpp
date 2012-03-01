#include "jtextstreamdatabasefactory.h"

#include <QCoreApplication>

#include "jtextstreamlogindb.h"
#include "jtextstreamuserinfodb.h"
#include "jtextstreamgameinfodb.h"
#include "jtextstreamserverinfodb.h"
#include "jteststreaminvitationcodedb.h"

JTextStreamDatabaseFactory::JTextStreamDatabaseFactory(QObject *parent)
	:JAbstractDatabaseFactory(parent)
{
	JTestStreamInvitationCodeDB::read();
}

JTextStreamDatabaseFactory::~JTextStreamDatabaseFactory()
{
	JTextStreamLoginDB::flush();
	JTextStreamUserInfoDB::flush();
	JTextStreamGameInfoDB::flush();
	JTextStreamServerInfoDB::flush();
	JTestStreamInvitationCodeDB::flush();
}

JTextStreamDatabaseFactory*
JTextStreamDatabaseFactory::createInstance(QObject* parent)
{
	JTextStreamDatabaseFactory* instance =
			new JTextStreamDatabaseFactory(parent);
	return instance;
}

JAbstractLoginDB*
JTextStreamDatabaseFactory::createLoginDB()
{
	return new JTextStreamLoginDB(this);
}

JAbstractUserInfoDB*
JTextStreamDatabaseFactory::createUserInfoDB()
{
	return new JTextStreamUserInfoDB(this);
}

JAbstractGameInfoDB*
JTextStreamDatabaseFactory::createGameInfoDB()
{
	return new JTextStreamGameInfoDB(this);
}

JAbstractServerInfoDB*
JTextStreamDatabaseFactory::createServerInfoDB()
{
	return new JTextStreamServerInfoDB(this);
}

JAbstractInvitationCodeDB*
JTextStreamDatabaseFactory::createInvitationCodeDB()
{
	return new JTestStreamInvitationCodeDB(this);
}
