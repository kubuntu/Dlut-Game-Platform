#ifndef JABSTRACTUSERINFODB_H
#define JABSTRACTUSERINFODB_H

#include <QObject>

#include <DataStruct/JUserInfo>

class JAbstractUserInfoDB : public QObject
{
public:
	explicit JAbstractUserInfoDB(QObject *parent = 0):QObject(parent){}
	virtual JUserInfo getUserInfoById(JID id)=0;
	virtual JCode updateUserInfo(const JUserInfo& userinfo)=0;
	virtual bool isUserIdExist(JID id)=0;
	virtual JCode insertUserInfo(const JUserInfo& userinfo)=0;
};

#endif // JABSTRACTUSERINFODB_H
