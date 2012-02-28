#include "jabstractlogindb.h"

JAbstractLoginDB::JAbstractLoginDB(QObject *parent)
	:QObject(parent)
{
}

bool JAbstractLoginDB::checkPasswd(JID userId,const QString& passwd){
	QString realPswd = getPassword(userId) ;
	
	return realPswd == passwd ;
}

bool JAbstractLoginDB::checkRole(JID userId,ERole role){
	JRoleCombination rc = getRoleCombination(userId) ;
	
	return rc & (1<<role);
}
