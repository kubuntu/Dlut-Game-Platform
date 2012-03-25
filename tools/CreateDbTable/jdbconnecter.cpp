#include "jdbconnecter.h"

#include <QSqlDatabase>
#include <QSqlError>

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
		dgpDB.setUserName(password);
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

const QString& JDbConnecter::errorString()const{
	return m_error ;
}
