#ifndef JTEXTSTREAMSERVERINFODB_H
#define JTEXTSTREAMSERVERINFODB_H

#include "../jabstractserverinfodb.h"

class JTextStreamServerInfoDB : public JAbstractServerInfoDB
{
public:
    explicit JTextStreamServerInfoDB(QObject *parent = 0);
	JServerInfo getServerInfoById(JID id);
	JCode updateServerInfo(const JServerInfo& serverinfo);
	bool isServerIdExist(JID id);
	JCode insertServerInfo(const JServerInfo& serverinfo);

	static void flush();
};

#endif // JTEXTSTREAMSERVERINFODB_H
