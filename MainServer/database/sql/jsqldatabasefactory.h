#ifndef JSQLDATABASEFACTORY_H
#define JSQLDATABASEFACTORY_H

#include "../jabstractdatabasefactory.h"

class JSQLDatabaseFactory : public JAbstractDatabaseFactory
{
	Q_OBJECT
public:
	static JSQLDatabaseFactory *createInstance(QObject* parent);
protected:
	JAbstractLoginDB *createLoginDB();
	JAbstractUserInfoDB *createUserInfoDB();
	JAbstractGameInfoDB *createGameInfoDB();
	JAbstractServerInfoDB *createServerInfoDB();
private:
	explicit JSQLDatabaseFactory(QObject *parent = 0);
private slots:
	void on_application_aboutToQuit();
};

#endif // JSQLDATABASEFACTORY_H
