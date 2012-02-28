#ifndef JABSTRACTLOGINDB_H
#define JABSTRACTLOGINDB_H

#include <QObject>

#include "Global/Global"
#include <Global/Login>

class JAbstractLoginDB : public QObject
{
public:
	explicit JAbstractLoginDB(QObject *parent = 0);
	
	/// return -1 if no such user;
	virtual JID checkLoginName(const QString& loginname)=0;
	virtual QString getLoginName(JID userId)=0;
	virtual QString getPassword(JID userId)=0;
	virtual void setPassword(JID userId , const QString& pswd)=0;
	virtual JCode addLoginUser(const QString& loginname,const QString& password)=0;
	virtual JRoleCombination getRoleCombination(JID userId)=0;
	virtual void setRoleCombination(JID userId,JRoleCombination role)=0;
	
	// helper function
	bool checkPasswd(JID,const QString& passwd);
	bool checkRole(JID userId,ERole role);
};

#endif // JABSTRACTLOGINDB_H
