#ifndef JSQLUSERINFODB_H
#define JSQLUSERINFODB_H

#include "../jabstractuserinfodb.h"

class QSqlDatabase;

class JSQLUserInfoDB : public JAbstractUserInfoDB
{
public:
	explicit JSQLUserInfoDB(QObject *parent = 0);
	JUserInfo getUserInfoById(JID userID);
	JCode updateUserInfo(const JUserInfo &userInfo);
	void testUserinfoExist(JID userID);
};

#endif // JSQLUSERINFODB_H
