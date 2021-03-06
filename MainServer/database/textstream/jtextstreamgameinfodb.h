#ifndef JTEXTSTREAMGAMEINFODB_H
#define JTEXTSTREAMGAMEINFODB_H

#include "../jabstractgameinfodb.h"

class JTextStreamGameInfoDB : public JAbstractGameInfoDB
{
public:
    explicit JTextStreamGameInfoDB(QObject *parent = 0);
	JGameInfo getGameInfoById(JID id);
	JGameList getGameList();
	JCode updateGameInfo(const JGameInfo& gameinfo);
	bool isGameIdExist(JID id);
	JCode insertGameInfo(const JGameInfo& gameinfo);

	static void flush();
};

#endif // JTEXTSTREAMGAMEINFODB_H
