#include "jsqllogindb.h"

#include "jsqlcommon.h"

#include <Global/Global>
#include <Global/Login>
#include <Global/Register>
#include <Global/CodeError>

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

JSQLLoginDB::JSQLLoginDB(QObject *parent) :
	JAbstractLoginDB(parent)
{
}


JID JSQLLoginDB::checkLoginName(const QString &loginName) {
	QSqlQuery query;
	PREPARE(query , 
			"SELECT user_id FROM logininfo "
			"WHERE user_name = :loginName" ,
			-1 ) ;
	
	query.bindValue(":loginName", loginName);
	
	EXEC( query , -1 );
	
	if (query.next())
		return query.value(0).toInt();
	else return -1;
}

QString JSQLLoginDB::getLoginName(JID userID) {
	QSqlQuery query ;
	PREPARE( query , 
			"SELECT user_name FROM logininfo "
			"WHERE user_id = :userID" ,
			QString() );
	
	query.bindValue(":userID", userID);
	
	EXEC( query , QString() );
	
	if (query.next())
		return query.value(0).toString();
	else
		return QString();
}

QString JSQLLoginDB::getPassword(JID userID) {
	QSqlQuery query ;
	PREPARE( query , 
			"SELECT passwd FROM logininfo "
			"WHERE user_id = :userID" ,
			QString() );
	
	query.bindValue(":userID", userID);
	
	EXEC( query , QString() );
	
	if (query.next()) {
		return query.value(0).toString();
	} else {
		return QString() ;
	}
}

void JSQLLoginDB::setPassword(JID userId , const QString& pswd)
{
	QSqlQuery query ;
	PREPARE( query , 
			" UPDATE logininfo "
			"SET passwd = :passwd "
			"WHERE user_id = :userID" ,
			);
	
	query.bindValue(":userID",userId);
	query.bindValue(":passwd", pswd);
	
	EXEC( query , );
}

JCode JSQLLoginDB::addLoginUser(const QString &loginName, const QString &passwd) {
	QSqlQuery query ;
	PREPARE( query , 
			"INSERT INTO logininfo "
			"(user_name, passwd, roles) "
			"VALUES(:loginName, :passwd, :roles)" ,
			EPrepareFailed );
	
	query.bindValue(":loginName", loginName);
	query.bindValue(":passwd", passwd);
	query.bindValue(":roles", 1 << ROLE_GAMEPLAYER);
	
	EXEC( query , EExecFailed );
	return 0;
}

JRoleCombination JSQLLoginDB::JSQLLoginDB::getRoleCombination(JID userID) {
	QSqlQuery query ;
	PREPARE( query ,
			"SELECT roles FROM logininfo "
			"WHERE user_id = :userID" ,
			0 );
	
	query.bindValue(":userID", userID);
	
	EXEC( query , 0 );
	
	if (query.next()) {
		return query.value(0).toInt();
	}else{
		return 0;
	}
}

void JSQLLoginDB::setRoleCombination(JID userID, JRoleCombination roles) {
	QSqlQuery query ;
	PREPARE( query , 
			"UPDATE logininfo "
			"SET roles = :roles "
			"WHERE user_id = :userID" ,
			);
	
	query.bindValue(":roles", roles);
	query.bindValue(":user_ID", userID);
	
	EXEC( query , );
}
