#ifndef JSQLSERVERINFODB_H
#define JSQLSERVERINFODB_H

#include "../jabstractserverinfodb.h"

class QSqlDatabase;

class JSQLServerInfoDB : public JAbstractServerInfoDB
{
public:
	explicit JSQLServerInfoDB(QSqlDatabase *dgpDB, QObject *parent = 0);
	JServerInfo getServerInfoById(JID ID);
	JCode updateServerInfo(const JServerInfo &serverInfo);
	bool isServerIdExist(JID id);
	JCode insertServerInfo(const JServerInfo& serverinfo);

private:
	QSqlDatabase *serverInfoDB;
};

#endif // JSQLSERVERINFODB_H
