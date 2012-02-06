#ifndef JSQLGAMEINFODB_H
#define JSQLGAMEINFODB_H

#include "../jabstractgameinfodb.h"

class QSqlDatabase;

class JSQLGameInfoDB : public JAbstractGameInfoDB
{
public:
	explicit JSQLGameInfoDB(QSqlDatabase *dgpDB, QObject *parent = 0);
	JGameInfo getGameInfoById(JID ID);
	JGameList getGameList();
	JCode updateGameInfo(const JGameInfo &gameInfo);
	bool isGameIdExist(JID id);
	JCode insertGameInfo(const JGameInfo& gameinfo);

private:
	QSqlDatabase *gameInfoDB;

};

#endif // JSQLGAMEINFODB_H
