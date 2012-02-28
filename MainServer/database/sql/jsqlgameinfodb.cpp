#include "jsqlgameinfodb.h"

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

JSQLGameInfoDB::JSQLGameInfoDB(QObject *parent) :
	JAbstractGameInfoDB(parent)
{
}

JGameInfo JSQLGameInfoDB::getGameInfoById(JID ID) {
	qDebug() << "+ getGameInfoById" <<endl;
	QSqlQuery *gameInfoQuery = new QSqlQuery;
	if (gameInfoQuery->prepare("SELECT game_name,		\n"
									"version,			\n"
									"author_id,			\n"
									"runner_id,			\n"
									"intro,				\n"
									"server_id,			\n"
									"download_url		\n"
							   "FROM gameinfo			\n"
							   "WHERE game_id = :gameID"))
		qDebug() << "getGameInfoById prepare succ";
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		qDebug() << "getGameInfoById prepare fail";
	}
	gameInfoQuery->bindValue(":gameID", ID);
	if (gameInfoQuery->exec())
		qDebug() << "getGameInfoById exec succ";
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		qDebug() << "getGameInfoById exec fail";
	}
	//without gameID checking...
	if (gameInfoQuery->next())
		return JGameInfo(ID,
						 gameInfoQuery->value(0).toString(),
						 JVersion((quint32)gameInfoQuery->value(1).toInt()),
						 gameInfoQuery->value(2).toInt(),
						 gameInfoQuery->value(3).toInt(),
						 gameInfoQuery->value(4).toString(),
						 gameInfoQuery->value(5).toInt(),
						 QUrl(gameInfoQuery->value(6).toString())
						 );
	else
		return JGameInfo();
}

JGameList JSQLGameInfoDB::getGameList() {
	qDebug() << "+ getGameList";
	QSqlQuery *gameInfoQuery = new QSqlQuery();
	if (gameInfoQuery->exec("SELECT game_id, game_name FROM gameinfo"))
		qDebug() << "getGameList exec succ";
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		qDebug() << "getGameList exec fail";
	}
	JGameList gameList;
	while (gameInfoQuery->next()) {
		gameList.insert(gameInfoQuery->value(0).toInt(),
						gameInfoQuery->value(1).toString()
						);
	}
	return gameList;
}

JCode JSQLGameInfoDB::updateGameInfo(const JGameInfo &gameInfo) {
	qDebug() << "+ updateGameInfo";
	QSqlQuery gameInfoQuery;
	qDebug() << gameInfo.getGameId()
			 << gameInfo.getName()
			 << gameInfo.getVersion().getData()
			 << gameInfo.getAuthor()
			 << gameInfo.getRunner()
			 << gameInfo.getIntroduction()
			 << gameInfo.getServerId()
			 << gameInfo.getDownloadUrl().toString();
	if (gameInfoQuery.prepare("UPDATE gameinfo	SET				\n"
									"game_name = :gameName,		\n"
									"version = :version,		\n"
									"author_id = :authorID,		\n"
									"runner_id = :runnerID,		\n"
									"intro = :introdution,		\n"
									"server_id = :serverID,		\n"
									"download_url = :downUrl	\n"
							   "WHERE game_id = :gameID"))
		qDebug() << "updateGameInfo prepare succ";
	else {
		qDebug() << gameInfoQuery.lastError().databaseText();
		qDebug() << "upDataGameInfo prepare fail";
	}
	gameInfoQuery.bindValue(":gameName", gameInfo.getName());
	gameInfoQuery.bindValue(":version", gameInfo.getVersion().getData());
	gameInfoQuery.bindValue(":authorID", gameInfo.getAuthor());
	gameInfoQuery.bindValue(":runnerID", gameInfo.getRunner());
	gameInfoQuery.bindValue(":introdution", gameInfo.getIntroduction());
	gameInfoQuery.bindValue(":serverID", gameInfo.getServerId());
	gameInfoQuery.bindValue(":downUrl", gameInfo.getDownloadUrl().toString());
	gameInfoQuery.bindValue(":gameID", gameInfo.getGameId());
	if (gameInfoQuery.exec()) {
		qDebug() << "updateGameInfo exec succ";
		return 0;
	}
	else {
		qDebug() << gameInfoQuery.lastError().databaseText();
		return -1;//undefined
	}
}

bool JSQLGameInfoDB::isGameIdExist(JID id)
{
	QSqlQuery gameInfoQuery;
	if (gameInfoQuery.prepare(
			"select game_id from gameinfo "
			"where game_id= :gameID"))
		qDebug() << __FUNCTION__ << " prepare succ";
	else {
		qDebug() << gameInfoQuery.lastError().databaseText();
		qDebug() << __FUNCTION__ << " prepare fail";
	}

	gameInfoQuery.bindValue(":gameID", id);
	if (gameInfoQuery.exec()) {
		qDebug() << __FUNCTION__ << " exec succ";
		if(gameInfoQuery.size() > 0){
			return true;
		}else{
			return false;
		}
	}
	else {
		qDebug() << gameInfoQuery.lastError().databaseText();
		return false;
	}
}

JCode JSQLGameInfoDB::insertGameInfo(const JGameInfo& gameInfo)
{
	QSqlQuery gameInfoQuery;
	if (gameInfoQuery.prepare(
			" INSERT INTO gameinfo "
			" (game_id,game_name,version,author_id,runner_id,intro,server_id,download_url) "
			" values(:gameID,:gameName,:version,:authorID,:runnerID,:introduction,:serverID,:downUrl) "))
		qDebug() << __FUNCTION__ << " prepare succ";
	else {
		qDebug() << gameInfoQuery.lastError().databaseText();
		qDebug() << __FUNCTION__ << " prepare fail";
	}
	gameInfoQuery.bindValue(":gameName", gameInfo.getName());
	gameInfoQuery.bindValue(":version", gameInfo.getVersion().getData());
	gameInfoQuery.bindValue(":authorID", gameInfo.getAuthor());
	gameInfoQuery.bindValue(":runnerID", gameInfo.getRunner());
	gameInfoQuery.bindValue(":introduction", gameInfo.getIntroduction());
	gameInfoQuery.bindValue(":serverID", gameInfo.getServerId());
	gameInfoQuery.bindValue(":downUrl", gameInfo.getDownloadUrl().toString());
	gameInfoQuery.bindValue(":gameID", gameInfo.getGameId());
	if (gameInfoQuery.exec()) {
		qDebug() << __FUNCTION__ << " exec succ";
		return 0;
	}
	else {
		qDebug() << gameInfoQuery.lastError().databaseText();
		return -1;//undefined
	}
}
