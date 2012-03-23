#include "jdbconnecter.h"

#include <QSqlDatabase>
#include <QSqlError>

bool JDbConnecter::connect(
		const QString& drive,
		const QString& database,
		const QString& username,
		const QString& password
	){
	QSqlDatabase dgpDB = QSqlDatabase::addDatabase(drive) ;
	if( ! dgpDB.isValid() ){
		m_error = " drive not valid .";
		return false;
	}
	
	dgpDB.setDatabaseName(database) ;
	dgpDB.setUserName(username);
	dgpDB.setPassword(password) ;
	
	if (!dgpDB.open()) {
		m_error = dgpDB.lastError().databaseText() ;
		return false;
	}
	
	return true;
}

const QString& JDbConnecter::errorString()const{
	return m_error ;
}
