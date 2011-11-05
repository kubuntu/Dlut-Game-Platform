#ifndef JABSTRACTLOGINDB_H
#define JABSTRACTLOGINDB_H

#include <QObject>

#include "Global/Global"

class JAbstractLoginDB : public QObject
{
public:
	explicit JAbstractLoginDB(QObject *parent = 0);
	virtual JID checkLoginName(const QString& loginname)=0;
	virtual bool checkPasswd(JID,const QString& passwd)=0;
	virtual bool checkRole(JID,JID)=0;
};

#endif // JABSTRACTLOGINDB_H