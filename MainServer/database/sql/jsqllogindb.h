#ifndef JSQLLOGINDB_H
#define JSQLLOGINDB_H

#include "../jabstractlogindb.h"

class JSQLLoginDB : public JAbstractLoginDB
{
public:
	explicit JSQLLoginDB(QObject *parent = 0);
	JID checkLoginName(const QString &loginName);
	QString getLoginName(JID userID);
	QString getPassword(JID userID);
	void setPassword(JID userId , const QString& pswd);
	JRoleCombination getRoleCombination(JID userID);
	JCode addLoginUser(const QString &loginName, const QString &passwd);
	void setRoleCombination(JID userID, JRoleCombination roles);
};

#endif // JSQLLOGINDB_H
