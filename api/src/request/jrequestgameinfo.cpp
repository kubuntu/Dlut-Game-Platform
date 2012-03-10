#include "jrequestgameinfo.h"

using namespace NetworkData;

/*!
	\file jrequestgameinfo.h
	\brief 定义了 JRequestGameInfo 类
*/

/*!
	\class JRequestGameInfo jrequestgameinfo.h
	\ingroup client
	\brief 向服务器发送请求的基类。
*/

JRequestGameInfo::JRequestGameInfo(QObject *parent) :
    JInformationRequestBase(parent)
{
}

JGameInfo JRequestGameInfo::pullGameInfo(JID gameId,int msecs)
{
	JGameInfo gi(gameId);
	gi.fromByteArray(pullInformationDataById(gameId,msecs));
	return gi;
}

JGameList JRequestGameInfo::pullGameList(int msecs)
{
	JGameList gl;
	gl.fromByteArray(pullInformationData(gl.head(),msecs));
	return gl;
}


NetworkData::JHead JRequestGameInfo::getHeadById(JID id) const
{
	return JGameInfo(id).head();
}
