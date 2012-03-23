#include "jdgpdbtablecreater.h"

#include <QSqlQuery>
#include <QSqlError>

bool JDgpDbTableCreater::create(){
	m_error=" unfinished function ";
	const int NUM_TABLE = 5 ;
	const static QString strSqls[][2] = {
		{
			"logininfo",
			"CREATE TABLE `logininfo` ( "
			"`user_id` int(10) NOT NULL AUTO_INCREMENT, "
			"`user_name` varchar(50) NOT NULL, "
			"`passwd` varchar(50) NOT NULL, "
			"`roles` tinyint(3) NOT NULL DEFAULT '0', "
			"PRIMARY KEY (`user_id`), "
			"UNIQUE KEY `user_name` (`user_name`) "
			") AUTO_INCREMENT=1001"
		},
		{
			"userinfo",
			"CREATE TABLE `userinfo` ( "
			"`user_id` int(10) NOT NULL AUTO_INCREMENT, "
			"`nickname` varchar(50) DEFAULT NULL, "
			"`org` text, "
			"PRIMARY KEY (`user_id`) "
			") AUTO_INCREMENT=1001"
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
			") "
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
			")"
		},
		{
			"invitationCode",
			"CREATE TABLE `invitationCode` ( "
			"`id` int(11) NOT NULL AUTO_INCREMENT, "
			"`code` varchar(50) NOT NULL, "
			"PRIMARY KEY (`id`) "
			")"
		},
	};
	
	QSqlQuery query;
	int i;
	for(i=0;i<NUM_TABLE;++i){
		if( ! query.exec(strSqls[i][1]) ){
			m_error = QString("create table %1 failed : %2")
						.arg(strSqls[i][0])
						.arg(query.lastError().text());
			return false;
		}
	}
	return false;
}

const QString& JDgpDbTableCreater::errorString()const{
	return m_error ;
}
