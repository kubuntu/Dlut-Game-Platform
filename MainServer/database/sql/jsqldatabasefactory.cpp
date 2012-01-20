#include "jsqldatabasefactory.h"

#include "jsqllogindb.h"
#include "jsqluserinfodb.h"
#include "jsqlgameinfodb.h"
#include "jsqlserverinfodb.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextCodec>

#include <QSettings>
#include <QStringList>
#include <QCoreApplication>

#include <QDebug>

JSQLDatabaseFactory::JSQLDatabaseFactory(QObject *parent) :
	JAbstractDatabaseFactory(parent)
{
	dgpDB = new QSqlDatabase;

	dgpdbIni = new QSettings("dgpdb.ini", QSettings::IniFormat);
	if (dgpdbIni->allKeys().empty()) {
		qDebug() << "dgpdb.ini not found!";
		return ;
	}

//	if (!connectCount++) {
//		qDebug() << "connectCount = " << connectCount;

//		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//		QTextCodec::setCodecForCStrings(codec);
//		QTextCodec::setCodecForTr(codec);
	qDebug() << "dgpdb.ini read ";

	if (dgpdbIni->value("drive").toString() == "mysql") {
		qDebug() << "database type: MySQL";
		dgpdbIni->beginGroup("MySQL");
		*dgpDB = QSqlDatabase::addDatabase("QMYSQL", "dgpdb");
		dgpDB->setDatabaseName(dgpdbIni->value("database").toString());
		dgpDB->setUserName(dgpdbIni->value("user").toString());
		dgpDB->setPassword(dgpdbIni->value("password").toString());
		dgpdbIni->endGroup();
//		dgpDB->setHostName("localhost");
//		dgpDB->setDatabaseName("dgpdb");
//		dgpDB->setUserName("dgproot");
//		dgpDB->setPassword("dgproot");
	} else if (dgpdbIni->value("drive").toString() == "sqlite") {
		qDebug() << "database type: SQLite";
		dgpdbIni->beginGroup("SQLite");
		*dgpDB = QSqlDatabase::addDatabase("QSQLITE", "dgpdb");
		dgpDB->setDatabaseName(dgpdbIni->value("database").toString());
		dgpdbIni->endGroup();
	} else {
		qDebug() << "the profile of database is incomplete";
		qDebug() << "Field \"drive\" not found";
	}
		if (dgpDB->open()) {
			qDebug() << "dgpdb connect...";
//			dgpDB->exec("SET NAMES 'latin1'");
		} else {
			qDebug() << dgpDB->lastError().databaseText();
			qDebug() << "dgpdb connect fali...";
		}
    connect(QCoreApplication::instance(),
            SIGNAL(aboutToQuit()),
            SLOT(on_application_aboutToQuit()));
}


JSQLDatabaseFactory* JSQLDatabaseFactory::getInstance() {
	qDebug() << "++ JSQLDatabaseFactory getInstance";
	static QObject parent;
	static JSQLDatabaseFactory* instance = new JSQLDatabaseFactory(&parent);
	return instance;
}

JAbstractLoginDB* JSQLDatabaseFactory::createLoginDB() {
	qDebug() << "++ JSQLDatabaseFactory createLoginDB";
	return new JSQLLoginDB(dgpDB, this);
}

JAbstractUserInfoDB* JSQLDatabaseFactory::createUserInfoDB() {
	qDebug() << "++ JSQLDatabaseFactory createUserInfoDB";
	return new JSQLUserInfoDB(dgpDB, this);
}

JAbstractGameInfoDB* JSQLDatabaseFactory::createGameInfoDB() {
	qDebug() << "++ JSQLDatabaseFactory createGameInfoDB";
	return new JSQLGameInfoDB(dgpDB, this);
}

JAbstractServerInfoDB* JSQLDatabaseFactory::createServerInfoDB() {
	qDebug() << "++ JSQLDatabaseFactory createServerInfoDB";
	return new JSQLServerInfoDB(dgpDB, this);
}

void JSQLDatabaseFactory::on_application_aboutToQuit()
{
    qDebug()<<__FUNCTION__;
    dgpDB->close();
    delete dgpDB;
    dgpDB = NULL ;
    QSqlDatabase::removeDatabase( "dgpdb" );
}
