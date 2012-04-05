#include "jdbconnecter.h"

#include <QSqlDatabase>
#include <QSqlError>

/*!
	\file jdbconnecter.h
	\brief 定义了 JDbConnecter 类
*/

/*!
	\class JDbConnecter jdbconnecter.h "JDbConnecter"
	\brief 连接数据库
	
	命令行工具的一部分。\n
	调用 connect() 函数连接数据库。\n
	调用 errorString() 函数返回连接过程中发生的错误。
*/

/*!
	\brief 连接数据库。
	
	参数 \a argumentMap 是通过 JArgumentAnalyzer 类得到的参数表。\n
	成功返回 true ， 失败返回 false 。
	
	\sa JArgumentAnalyzer
*/
bool JDbConnecter::connect(
		const QMap<QString,QString>& argumentMap
	){
	
	// drive
	QString drive = argumentMap.value("drive");
	QSqlDatabase dgpDB = QSqlDatabase::addDatabase(drive) ;
	if( ! dgpDB.isValid() ){
		m_error = " drive not valid .";
		return false;
	}
	
	// database
	QString database = argumentMap.value("database");
	dgpDB.setDatabaseName(database) ;
	
	// username
	if(argumentMap.contains("username") ){
		QString username = argumentMap.value("username");
		dgpDB.setUserName(username);
	}
	
	// password
	if(argumentMap.contains("password") ){
		QString password = argumentMap.value("password");
		dgpDB.setPassword(password);
	}
	
	// hostname
	if(argumentMap.contains("hostname") ){
		QString hostname = argumentMap.value("hostname");
		dgpDB.setUserName(hostname);
	}
	
	if (!dgpDB.open()) {
		m_error = dgpDB.lastError().databaseText() ;
		return false;
	}
	
	return true;
}

/*!
	\brief 返回错误字符串
*/
const QString& JDbConnecter::errorString()const{
	return m_error ;
}
