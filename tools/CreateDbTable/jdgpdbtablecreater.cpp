#include "jdgpdbtablecreater.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

const static int NUM_TABLE = 5 ;
const static QString strSqls[][3] = {
	{
		"logininfo",
		
		"CREATE TABLE `logininfo` ( "
		"`user_id` int(10) NOT NULL AUTO_INCREMENT, "
		"`user_name` varchar(50) NOT NULL, "
		"`passwd` varchar(50) NOT NULL, "
		"`roles` tinyint(3) NOT NULL DEFAULT '0', "
		"PRIMARY KEY (`user_id`), "
		"UNIQUE KEY `user_name` (`user_name`) "
		") AUTO_INCREMENT=1001",
		
		"CREATE TABLE logininfo( "
		"user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"user_name VARCHAR(50) NOT NULL UNIQUE, "
		"passwd VARCHAR(50) NOT NULL,"
		"roles INTEGER NOT NULL DEFAULT '0');"
		"INSERT INTO SQLITE_SEQUENCE "
		"VALUES('logininfo', '1000');",
	},
	{
		"userinfo",
		
		"CREATE TABLE `userinfo` ( "
		"`user_id` int(10) NOT NULL AUTO_INCREMENT, "
		"`nickname` varchar(50) DEFAULT NULL, "
		"`org` text, "
		"PRIMARY KEY (`user_id`) "
		")",
		
		"CREATE TABLE userinfo( "
		"user_id INTEGER PRIMARY KEY, "
		"nickname VARCHAR(50), "
		"org TEXT) "
	},
	{
		"gameinfo",
		
		"CREATE TABLE `gameinfo` ( "
		"`game_id` int(10) NOT NULL AUTO_INCREMENT, "
		"`game_name` varchar(50) NOT NULL, "
		"`version` int(10) DEFAULT NULL, "
		"`author_id` int(10) DEFAULT NULL, "
		"`runner_id` int(10) DEFAULT NULL, "
		"`server_id` int(10) DEFAULT NULL, "
		"`download_url` varchar(255) DEFAULT NULL, "
		"`intro` text, "
		"PRIMARY KEY (`game_id`), "
		"UNIQUE KEY `game_name` (`game_name`) "
		") ",
		
		"CREATE TABLE gameinfo( "
		"game_id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"game_name VARCHAR(50) NOT NULL UNIQUE, "
		"version INTEGER, "
		"author_id INTEGER, "
		"runner_id INTEGER, "
		"server_id INTEGER, "
		"download_url VARCHAR(255), "
		"intro TEXT)"
	},
	{
		"serverinfo",
		
		"CREATE TABLE `serverinfo` ( "
		"`server_id` int(10) NOT NULL AUTO_INCREMENT, "
		"`server_name` varchar(50) NOT NULL, "
		"`runner_id` int(10) DEFAULT NULL, "
		"`host_addr` varchar(255) DEFAULT NULL, "
		"`host_port` smallint(5) DEFAULT NULL, "
		"PRIMARY KEY (`server_id`), "
		"UNIQUE KEY `server_name` (`server_name`) "
		")",
		
		"CREATE TABLE serverinfo( "
		"server_id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"server_name VARCHAR(50) NOT NULL UNIQUE, "
		"runner_id INTEGER, "
		"host_addr VARCHAR(255), "
		"host_port INTEGER)"
	},
	{
		"invitationCode",
		
		"CREATE TABLE `invitationCode` ( "
		"`id` int(11) NOT NULL AUTO_INCREMENT, "
		"`code` varchar(50) NOT NULL, "
		"PRIMARY KEY (`id`) "
		")",
		
		"CREATE TABLE `invitationCode` ( "
		"`id` INTEGER PRIMARY KEY AUTOINCREMENT, "
		"`code` varchar(50) NOT NULL "
		")"
	},
};

bool JDgpDbTableCreater::create(){
	QString driverName = QSqlDatabase::database().driverName();
	int k=0;
	if( driverName == "QMYSQL" ){
		k=1;
	}else if( driverName == "QSQLITE" ){
		k=2;
	}else{
		m_error = QString("unsupported driver : %1").arg(driverName);
		return false;
	}
	
	QSqlQuery query;
	int i;
	for(i=0;i<NUM_TABLE;++i){
		if( ! query.exec(strSqls[i][k]) ){
			m_error = QString("create table %1 failed : %2")
						.arg(strSqls[i][0])
						.arg(query.lastError().text());
			return false;
		}
	}
	return true;
}

const QString& JDgpDbTableCreater::errorString()const{
	return m_error ;
}
