#ifndef JABSTRACTSERVERINFODB_H
#define JABSTRACTSERVERINFODB_H

#include <QObject>

#include <DataStruct/JServerInfo>

class JAbstractServerInfoDB : public QObject
{
public:
    explicit JAbstractServerInfoDB(QObject *parent = 0):QObject(parent){}
	virtual JServerInfo getServerInfoById(JID id)=0;
	virtual JCode updateServerInfo(const JServerInfo& serverinfo)=0;
	virtual bool isServerIdExist(JID id)=0;
	virtual JCode insertServerInfo(const JServerInfo& serverinfo)=0;
};

#endif // JABSTRACTSERVERINFODB_H
