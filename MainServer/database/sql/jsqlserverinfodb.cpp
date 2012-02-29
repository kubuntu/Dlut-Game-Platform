#include "jsqlserverinfodb.h"

#include "jsqlcommon.h"

#include <Global/CodeError>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

JSQLServerInfoDB::JSQLServerInfoDB(QObject *parent) :
	JAbstractServerInfoDB(parent)
{
}

JServerInfo JSQLServerInfoDB::getServerInfoById(JID ID) {
	QSqlQuery query ;
	PREPARE( query , 
			"SELECT server_name, "
			"runner_id, "
			"host_addr, "
			"host_port "
			"FROM serverinfo "
			"WHERE server_id = :serverID",
			JServerInfo() );
	
	query.bindValue(":serverID", ID);
	
	EXEC( query , JServerInfo() );
	
	if (query.next())
		return JServerInfo(ID,
						   query.value(0).toString(),
						   query.value(1).toInt(),
						   SHost(QHostAddress(query.value(2).toString()),
								 query.value(3).toInt())
						   );
	else
		return JServerInfo();
}

JCode JSQLServerInfoDB::updateServerInfo(const JServerInfo &serverInfo) {
	QSqlQuery query;
	PREPARE( query ,
			"UPDATE serverinfo SET "
			"server_name = :serverName, "
			"runner_id = :runnerID, "
			"host_addr = :hostAddr, "
			"host_port = :hostPort "
			"WHERE server_id = :serverID",
			EPrepareFailed
			);
	
	query.bindValue(":serverName", serverInfo.getName());
	query.bindValue(":runnerID", serverInfo.getRunner());
	query.bindValue(":hostAddr", serverInfo.getHost().m_address.toString());
	query.bindValue(":hostPort", serverInfo.getHost().m_port);
	query.bindValue(":serverID", serverInfo.getServerId());
	
	EXEC( query , EExecFailed );
	
	return 0 ;
}

bool JSQLServerInfoDB::isServerIdExist(JID id)
{
	QSqlQuery query;
	PREPARE( query ,
			"select server_id from serverinfo "
			" where server_id = :serverID",
			false );
	
	query.bindValue(":serverID", id);
	
	EXEC( query , false );
	
	if(query.size()>0){
		return true;
	}else{
		return false;
	}
}

JCode JSQLServerInfoDB::insertServerInfo(const JServerInfo& serverInfo)
{
	QSqlQuery query;
	PREPARE( query ,
			" INSERT INTO serverinfo "
			" (server_id,server_name,runner_id,host_addr,host_port) "
			" values(:serverID,:serverName,:runnerID,:hostAddr,:hostPort) ",
			EPrepareFailed);
	
	query.bindValue(":serverName", serverInfo.getName());
	query.bindValue(":runnerID", serverInfo.getRunner());
	query.bindValue(":hostAddr", serverInfo.getHost().m_address.toString());
	query.bindValue(":hostPort", serverInfo.getHost().m_port);
	query.bindValue(":serverID", serverInfo.getServerId());
	
	EXEC( query , EExecFailed );
	
	return 0 ;
}
