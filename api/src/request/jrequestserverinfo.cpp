#include "jrequestserverinfo.h"

using namespace NetworkData;

/*!
	\file jrequestserverinfo.h
	\brief 定义了 JRequestServerInfo 类
*/

/*!
	\class JRequestServerInfo jrequestserverinfo.h
	\ingroup client
	\brief 请求 gameserver 信息
*/

JRequestServerInfo::JRequestServerInfo(QObject *parent) :
    JInformationRequestBase(parent)
{
}

JServerInfo JRequestServerInfo::pullServerInfo(JID serverId,int msecs )
{
	JServerInfo si(serverId);
	si.fromByteArray(pullInformationDataById(serverId,msecs));
	return si;
}

JHead JRequestServerInfo::getHeadById(JID id)const
{
	return JServerInfo(id).head();
}
