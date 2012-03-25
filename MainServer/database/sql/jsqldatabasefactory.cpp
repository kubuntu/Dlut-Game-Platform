#include "jsqldatabasefactory.h"

#include "jsqllogindb.h"
#include "jsqluserinfodb.h"
#include "jsqlgameinfodb.h"
#include "jsqlserverinfodb.h"
#include "jsqlinvitationcodedb.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QSettings>
#include <QCoreApplication>

#include <QDebug>

JSQLDatabaseFactory::JSQLDatabaseFactory(QObject *parent) :
	JAbstractDatabaseFactory(parent)
{
	QSettings dgpdbIni ("dgpdb.ini", QSettings::IniFormat);
	QString drive = dgpdbIni.value("drive","QMYSQL").toString();
	
	QSqlDatabase dgpDB = QSqlDatabase::addDatabase(drive) ;
	
	dgpdbIni.beginGroup(drive) ;
	
	QString database = dgpdbIni.value("database").toString();
	dgpDB.setDatabaseName(database) ;
	
	if(dgpdbIni.contains("username") ){
		QString userName = dgpdbIni.value("username").toString();
		dgpDB.setUserName(userName);
	}
	
	if(dgpdbIni.contains("password") ){
		QString password = dgpdbIni.value("password").toString() ;
		dgpDB.setPassword(password) ;
	}
	
	if(dgpdbIni.contains("hostname") ){
		QString hostname = dgpdbIni.value("hostname").toString();
		dgpDB.setUserName(hostname);
	}
	
	dgpdbIni.endGroup() ;
	
	if (!dgpDB.open()) {
		qDebug() << "dgpdb connect failed : "
				<< dgpDB.lastError().databaseText() ;
	}
	connect(QCoreApplication::instance(),
			SIGNAL(aboutToQuit()),
			SLOT(on_application_aboutToQuit()));
}

JSQLDatabaseFactory* JSQLDatabaseFactory::createInstance(QObject* parent) {
	JSQLDatabaseFactory* instance = new JSQLDatabaseFactory(parent);
	return instance;
}

JAbstractLoginDB* JSQLDatabaseFactory::createLoginDB() {
	return new JSQLLoginDB(this);
}

JAbstractUserInfoDB* JSQLDatabaseFactory::createUserInfoDB() {
	return new JSQLUserInfoDB(this);
}

JAbstractGameInfoDB* JSQLDatabaseFactory::createGameInfoDB() {
	return new JSQLGameInfoDB(this);
}

JAbstractServerInfoDB* JSQLDatabaseFactory::createServerInfoDB() {
	return new JSQLServerInfoDB(this);
}

JAbstractInvitationCodeDB* JSQLDatabaseFactory::createInvitationCodeDB(){
	return new JSQLInvitationCodeDB(this);
}

void JSQLDatabaseFactory::on_application_aboutToQuit()
{
    qDebug()<<__FUNCTION__;
    QString name;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase( name );
}
