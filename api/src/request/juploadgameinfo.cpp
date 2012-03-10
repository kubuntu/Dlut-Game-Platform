#include "juploadgameinfo.h"

#include "../global/jgameinfo.h"

/*!
	\file juploadgameinfo.h
	\brief 定义了 JUploadGameInfo 类
*/

/*!
	\class JUploadGameInfo juploadgameinfo.h
	\ingroup client
	\brief 上传 gameInfo 信息
*/

using namespace NetworkData;

JUploadGameInfo::JUploadGameInfo(QObject *parent) :
    JInformationSendBase(parent)
{
}

JCode JUploadGameInfo::pushGameInfo(const JGameInfo& gameinfo,int msecs)
{
	return pushInformationData(
				gameinfo.getGameId(),
				gameinfo.toByteArray(),
				msecs);
}

JHead JUploadGameInfo::getHead(JID id)const
{
	return JGameInfo(id).head();
}
