#ifndef JSQLDATABASEFACTORY_H
#define JSQLDATABASEFACTORY_H

#include "../jabstractdatabasefactory.h"

class QSqlDatabase;
class QSettings;

class JSQLDatabaseFactory : public JAbstractDatabaseFactory
{
	Q_OBJECT
	explicit JSQLDatabaseFactory(QObject *parent = 0);
public:
	static JSQLDatabaseFactory *getInstance();
	JAbstractLoginDB *createLoginDB();
	JAbstractUserInfoDB *createUserInfoDB();
	JAbstractGameInfoDB *createGameInfoDB();
	JAbstractServerInfoDB *createServerInfoDB();

private:
	QSqlDatabase *dgpDB;
	QSettings *dgpdbIni;
private slots:
	void on_application_aboutToQuit();
};

#endif // JSQLDATABASEFACTORY_H
