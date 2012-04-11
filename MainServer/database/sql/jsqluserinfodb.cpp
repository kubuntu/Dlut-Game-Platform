#include "jsqluserinfodb.h"

#include "jsqlcommon.h"

#include <Global/CodeError>

#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

JSQLUserInfoDB::JSQLUserInfoDB(QObject *parent) :
	JAbstractUserInfoDB(parent)
{
}

JUserInfo JSQLUserInfoDB::getUserInfoById(JID userID) {
	QSqlQuery query ;
	PREPARE( query , 
			"SELECT nickname, org FROM userinfo "
			"WHERE user_id = :userID",
			JUserInfo() );
	
	query.bindValue(":userID", userID);
	
	EXEC( query , JUserInfo() );
	
	if (query.next())
		return JUserInfo(userID,
						 query.value(0).toString(),
						 query.value(1).toString()
						 );
	else
		return JUserInfo();
}

JCode JSQLUserInfoDB::updateUserInfo(const JUserInfo &userInfo) {
	QSqlQuery query ;
	PREPARE( query ,
			"UPDATE userinfo SET "
			"nickname = :nickname, "
			"org = :org "
			"WHERE user_id = :userID",
			EPrepareFailed
			);
	
	query.bindValue(":nickname", userInfo.getNickname());
	query.bindValue(":org", userInfo.getOrganization());
	query.bindValue(":userID", userInfo.getUserId());
	
	EXEC( query , EExecFailed );
	
	return 0 ;
}

bool JSQLUserInfoDB::isUserIdExist(JID id){
	QSqlQuery query;
	PREPARE( query ,
			"select * from userinfo "
			"where user_id = :userId" ,
			false );
	
	query.bindValue(":userId", id);
	
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

JCode JSQLUserInfoDB::insertUserInfo(const JUserInfo& userInfo){
	QSqlQuery query;
	PREPARE( query ,
			" INSERT INTO userinfo "
			" (user_id,nickname,org) "
			" values(:userId,:nickname,:org) ",
			EPrepareFailed );
	
	query.bindValue(":nickname", userInfo.getNickname());
	query.bindValue(":org", userInfo.getOrganization());
	query.bindValue(":userId", userInfo.getUserId());
	
	EXEC( query , EExecFailed );
	
	return 0 ;
}
