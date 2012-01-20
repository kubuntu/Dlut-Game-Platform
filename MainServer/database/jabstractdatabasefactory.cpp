#include "jabstractdatabasefactory.h"

#include "textstream/jtextstreamdatabasefactory.h"
#include "sql/jsqldatabasefactory.h"

#include <QSettings>

JAbstractDatabaseFactory::JAbstractDatabaseFactory(QObject *parent)
	:QObject(parent)
{
}

JAbstractDatabaseFactory* JAbstractDatabaseFactory::getInstance()
{
    QString type = "sql";
    QSettings dgpdbIni ("dgpdb.ini", QSettings::IniFormat);
    type=dgpdbIni.value("type","sql").toString();
    if(type =="textstream"){
        return JTextStreamDatabaseFactory::getInstance();
    }else if(type == "sql"){
        return JSQLDatabaseFactory::getInstance();
    }
    return NULL;
}
