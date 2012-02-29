#include "jsqluserinfodb.h"

#include "jsqlcommon.h"

#include <Global/CodeError>

#include <QSqlQuery>
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
