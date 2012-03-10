#include "juploadserverinfo.h"

#include "../global/jserverinfo.h"

/*!
	\file juploadserverinfo.h
	\brief 定义了 JUploadServerInfo 类
*/

/*!
	\class JUploadServerInfo juploadserverinfo.h
	\ingroup client
	\brief 上传 gameserver 信息
*/

using namespace NetworkData;

JUploadServerInfo::JUploadServerInfo(QObject *parent) :
    JInformationSendBase(parent)
{
}

JCode JUploadServerInfo::pushServerInfo(const JServerInfo& serverinfo,int msecs)
{
	return pushInformationData(serverinfo.getServerId(),serverinfo.toByteArray(),msecs);
}

JHead JUploadServerInfo::getHead(JID id)const
{
	return JServerInfo(id).head();
}
