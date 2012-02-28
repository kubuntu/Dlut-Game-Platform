#include "jsqllogindb.h"

#include "jsqlcommon.h"

#include <Global/Global>
#include <Global/Login>
#include <Global/Register>
#include <Global/CodeError>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

JSQLLoginDB::JSQLLoginDB(QObject *parent) :
	JAbstractLoginDB(parent)
{
}


JID JSQLLoginDB::checkLoginName(const QString &loginName) {
	QSqlQuery query;
	if( ! query.prepare("SELECT user_id FROM logininfo "
						"WHERE user_name = :loginName") ){
		PREPARE_FAILED ;
		return -1;
	}
	
	query.bindValue(":loginName", loginName);
	query.exec();
	if (query.next())
		return query.value(0).toInt();
	else return -1;
}

QString JSQLLoginDB::getLoginName(JID userID) {
	QSqlQuery query ;
	if ( ! query.prepare("SELECT user_name FROM logininfo "
							"WHERE user_id = :userID")) {
		PREPARE_FAILED ;
		return QString() ;
	}
	
	query.bindValue(":userID", userID);
	
	if ( ! query.exec()) {
		EXEC_FAILED ;
		return QString() ;
	}
	
	if (query.next())
		return query.value(0).toString();
	else
		return QString();
}

QString JSQLLoginDB::getPassword(JID userID) {
	QSqlQuery query ;
	if ( ! query.prepare("SELECT passwd FROM logininfo "
							"WHERE user_id = :userID")){
		PREPARE_FAILED ;
		return QString() ;
	}
	
	query.bindValue(":userID", userID);
	
	if ( ! query.exec()) {
		EXEC_FAILED ;
		return QString() ;
	}
	
	if (query.next()) {
		return query.value(0).toString();
	} else {
		return QString() ;
	}
}

void JSQLLoginDB::setPassword(JID userId , const QString& pswd)
{
	QSqlQuery query ;
	if( ! query.prepare(" UPDATE logininfo "
							"SET passwd = :passwd "
							"WHERE user_id = :userID")){
		PREPARE_FAILED ;
		return ;
	}
	
	query.bindValue(":userID",userId);
	query.bindValue(":passwd", pswd);
	
	if( ! query.exec() ){
		EXEC_FAILED ;
		return ;
	}
}

JCode JSQLLoginDB::addLoginUser(const QString &loginName, const QString &passwd) {
	QSqlQuery query ;
	if ( ! query.prepare("INSERT INTO logininfo "
						"(user_name, passwd, roles) "
						"VALUES(:loginName, :passwd, :roles)")){
		PREPARE_FAILED ;
		return EPrepareFailed ;
	}
	
	query.bindValue(":loginName", loginName);
	query.bindValue(":passwd", passwd);
	query.bindValue(":roles", 1 << ROLE_GAMEPLAYER);
	
	if ( ! query.exec()) {
		EXEC_FAILED ;
		return EExecFailed ;
	}
	return 0;
}

JRoleCombination JSQLLoginDB::JSQLLoginDB::getRoleCombination(JID userID) {
	QSqlQuery query ;
	if( ! query.prepare("SELECT roles FROM logininfo "
						"WHERE user_id = :userID")){
		PREPARE_FAILED ;
		return 0 ;
	}
	
	query.bindValue(":userID", userID);
	
	if( ! query.exec() ){
		EXEC_FAILED ;
		return 0;
	}
	if (query.next()) {
		return query.value(0).toInt();
	}else{
		return 0;
	}
}

void JSQLLoginDB::setRoleCombination(JID userID, JRoleCombination roles) {
	QSqlQuery query ;
	if ( ! query.prepare("UPDATE logininfo "
							"SET roles = :roles "
							"WHERE user_id = :userID")){
		PREPARE_FAILED ;
		return ;
	}
	
	query.bindValue(":roles", roles);
	query.bindValue(":user_ID", userID);
	
	if ( ! query.exec()) {
		EXEC_FAILED ;
		return ;
	}
}
