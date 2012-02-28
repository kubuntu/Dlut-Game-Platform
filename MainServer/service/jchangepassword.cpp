#include "jchangepassword.h"

#include <Global/CodeError>

#include "../database/jabstractdatabasefactory.h"

JChangePassword::JChangePassword()
{
}

JCode JChangePassword::changePassword(
		JID userId,
		const QString& oldPassword,
		const QString& newPassword){
	
	// login db
	JAbstractDatabaseFactory* dbFactory=JAbstractDatabaseFactory::getInstance();
	JAbstractLoginDB* logindb=dbFactory->getLoginDB();
	
	// check oldPassword
	if( ! logindb->checkPasswd(userId,oldPassword)){
		return EPasswordError;
	}
	
	// set new password
	logindb->setPassword(userId,newPassword);
	
	return ESuccess ;
}
