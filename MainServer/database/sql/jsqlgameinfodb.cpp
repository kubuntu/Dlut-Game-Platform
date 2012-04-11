#include "jsqlgameinfodb.h"

#include "jsqlcommon.h"

#include <Global/CodeError>

#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

JSQLGameInfoDB::JSQLGameInfoDB(QObject *parent) :
	JAbstractGameInfoDB(parent)
{
}

JGameInfo JSQLGameInfoDB::getGameInfoById(JID ID) {
	QSqlQuery query ;
	PREPARE( query ,
			"SELECT game_name, "
			"version, "
			"author_id, "
			"runner_id, "
			"intro, "
			"server_id, "
			"download_url "
			"FROM gameinfo "
			"WHERE game_id = :gameID",
			JGameInfo() );
	
	query.bindValue(":gameID", ID);
	
	EXEC(query , JGameInfo() );
	
	if (query.next())
		return JGameInfo(ID,
						 query.value(0).toString(),
						 JVersion((quint32)query.value(1).toInt()),
						 query.value(2).toInt(),
						 query.value(3).toInt(),
						 query.value(4).toString(),
						 query.value(5).toInt(),
						 QUrl(query.value(6).toString())
						 );
	else
		return JGameInfo();
}

JGameList JSQLGameInfoDB::getGameList() {
	QSqlQuery query ;
	PREPARE( query ,
			"SELECT game_id, game_name FROM gameinfo",
			JGameList() );
	
	EXEC( query , JGameList() );
	
	JGameList gameList;
	while (query.next()) {
		gameList.insert(query.value(0).toInt(),
						query.value(1).toString()
						);
	}
	return gameList;
}

JCode JSQLGameInfoDB::updateGameInfo(const JGameInfo &gameInfo) {
	QSqlQuery query ;
	PREPARE( query ,
			"UPDATE gameinfo SET "
			"game_name = :gameName, "
			"version = :version, "
			"author_id = :authorID, "
			"runner_id = :runnerID, "
			"intro = :introdution, "
			"server_id = :serverID, "
			"download_url = :downUrl "
			"WHERE game_id = :gameID" ,
			EPrepareFailed );
	
	query.bindValue(":gameName", gameInfo.getName());
	query.bindValue(":version", gameInfo.getVersion().getData());
	query.bindValue(":authorID", gameInfo.getAuthor());
	query.bindValue(":runnerID", gameInfo.getRunner());
	query.bindValue(":introdution", gameInfo.getIntroduction());
	query.bindValue(":serverID", gameInfo.getServerId());
	query.bindValue(":downUrl", gameInfo.getDownloadUrl().toString());
	query.bindValue(":gameID", gameInfo.getGameId());
	
	EXEC( query , EExecFailed );
	
	return 0;
}

bool JSQLGameInfoDB::isGameIdExist(JID id)
{
	QSqlQuery query;
	PREPARE( query ,
			"select game_id from gameinfo "
			"where game_id= :gameID" ,
			false );
	
	query.bindValue(":gameID", id);
	
	EXEC( query , false );
	
	if( query.driver()->hasFeature(QSqlDriver::QuerySize) ){
		if(query.size() > 0){
			return true;
		}else{
			return false;
		}
	}else{
		if(query.next()){
			return true;
		}else{
			return false;
		}
	}
}

JCode JSQLGameInfoDB::insertGameInfo(const JGameInfo& gameInfo)
{
	QSqlQuery query;
	PREPARE( query ,
			" INSERT INTO gameinfo "
			" (game_id,game_name,version,author_id,runner_id,intro,server_id,download_url) "
			" values(:gameID,:gameName,:version,:authorID,:runnerID,:introduction,:serverID,:downUrl) ",
			EPrepareFailed );
	
	query.bindValue(":gameName", gameInfo.getName());
	query.bindValue(":version", gameInfo.getVersion().getData());
	query.bindValue(":authorID", gameInfo.getAuthor());
	query.bindValue(":runnerID", gameInfo.getRunner());
	query.bindValue(":introduction", gameInfo.getIntroduction());
	query.bindValue(":serverID", gameInfo.getServerId());
	query.bindValue(":downUrl", gameInfo.getDownloadUrl().toString());
	query.bindValue(":gameID", gameInfo.getGameId());
	
	EXEC( query , EExecFailed );
	
	return 0 ;
}
