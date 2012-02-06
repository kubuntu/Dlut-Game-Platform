#include "jsqlserverinfodb.h"

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

JSQLServerInfoDB::JSQLServerInfoDB(QSqlDatabase *dgpDB, QObject *parent) :
	JAbstractServerInfoDB(parent), serverInfoDB(dgpDB)
{
	qDebug() << "+ JSQLSerInfoDB constructed";
}

JServerInfo JSQLServerInfoDB::getServerInfoById(JID ID) {
	qDebug() << "+ getServerInfoById";
	QSqlQuery *serverInfoQuery = new QSqlQuery(*serverInfoDB);
	if (serverInfoQuery->prepare("SELECT server_name,	\n"
								 "runner_id,			\n"
								 "host_addr,			\n"
								 "host_port				\n"
								 "FROM serverinfo		\n"
								 "WHERE server_id = :serverID"))
		qDebug() << "getServerInfoById prepare succ";
	else {
		qDebug() << serverInfoQuery->lastError().databaseText();
		qDebug() << "getServerInfoById prepare fail";
	}
	serverInfoQuery->bindValue(":serverID", ID);
	if (serverInfoQuery->exec())
		qDebug() << "getServerInfoById exec succ";
	else {
		qDebug() << serverInfoQuery->lastError().databaseText();
		qDebug() << "getServerInfoId exec fail";
	}
	if (serverInfoQuery->next())
		return JServerInfo(ID,
						   serverInfoQuery->value(0).toString(),
						   serverInfoQuery->value(1).toInt(),
						   SHost(QHostAddress(serverInfoQuery->value(2).toString()),
								 serverInfoQuery->value(3).toInt())
						   );
	else
		return JServerInfo();
}

JCode JSQLServerInfoDB::updateServerInfo(const JServerInfo &serverInfo) {
	qDebug() << "+ updateServerInfo";
	QSqlQuery serverInfoQuery(*serverInfoDB);
	if (serverInfoQuery.prepare("UPDATE serverinfo SET				\n"
									"server_name = :serverName,	\n"
									"runner_id = :runnerID,		\n"
									"host_addr = :hostAddr,		\n"
									"host_port = :hostPort		\n"
								 "WHERE server_id = :serverID"))
		qDebug() << "updateServerInfo prepare succ";
	else {
		qDebug() << serverInfoQuery.lastError().databaseText();
		qDebug() << "updateServerInfo prepare fail";
	}
	serverInfoQuery.bindValue(":serverName", serverInfo.getName());
	serverInfoQuery.bindValue(":runnerID", serverInfo.getRunner());
	serverInfoQuery.bindValue(":hostAddr", serverInfo.getHost().m_address.toString());
	serverInfoQuery.bindValue(":hostPort", serverInfo.getHost().m_port);
	serverInfoQuery.bindValue(":serverID", serverInfo.getServerId());
	if (serverInfoQuery.exec()) {
		qDebug() << "updateServerInfo exec succ";
		return 0;
	}
	else {
		qDebug() << serverInfoQuery.lastError().databaseText();
		qDebug() << "updateServerInfo exec fail";
		return -1;
	}
}

bool JSQLServerInfoDB::isServerIdExist(JID id)
{
	QSqlQuery serverInfoQuery(*serverInfoDB);
	if (serverInfoQuery.prepare(
			"select server_id from serverinfo "
			" where server_id = :serverID"))
		qDebug() << __FUNCTION__ << " prepare succ";
	else {
		qDebug() << serverInfoQuery.lastError().databaseText();
		qDebug() << __FUNCTION__ << " prepare fail";
	}
	serverInfoQuery.bindValue(":serverID", id);
	if (serverInfoQuery.exec()) {
		qDebug() << __FUNCTION__ << " exec succ";
		if(serverInfoQuery.size()>0){
			return true;
		}else{
			return false;
		}
	}
	else {
		qDebug() << serverInfoQuery.lastError().databaseText();
		qDebug() << __FUNCTION__ << " exec fail";
		return false;
	}
}

JCode JSQLServerInfoDB::insertServerInfo(const JServerInfo& serverInfo)
{
	QSqlQuery serverInfoQuery(*serverInfoDB);
	if (serverInfoQuery.prepare(
			" INSERT INTO serverinfo "
			" (server_id,server_name,runner_id,host_addr,host_port) "
			" values(:serverID,:serverName,:runnerID,:hostAddr,:hostPort) "))
		qDebug() << __FUNCTION__ << " prepare succ";
	else {
		qDebug() << serverInfoQuery.lastError().databaseText();
		qDebug() << __FUNCTION__ << " prepare fail";
	}
	serverInfoQuery.bindValue(":serverName", serverInfo.getName());
	serverInfoQuery.bindValue(":runnerID", serverInfo.getRunner());
	serverInfoQuery.bindValue(":hostAddr", serverInfo.getHost().m_address.toString());
	serverInfoQuery.bindValue(":hostPort", serverInfo.getHost().m_port);
	serverInfoQuery.bindValue(":serverID", serverInfo.getServerId());
	if (serverInfoQuery.exec()) {
		qDebug() << __FUNCTION__ << " exec succ";
		return 0;
	}
	else {
		qDebug() << serverInfoQuery.lastError().databaseText();
		qDebug() << __FUNCTION__ << " exec fail";
		return -1;
	}
}
