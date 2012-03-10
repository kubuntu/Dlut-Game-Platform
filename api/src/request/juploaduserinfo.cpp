#include "juploaduserinfo.h"

#include "../global/juserinfo.h"

/*!
	\file juploaduserinfo.h
	\brief 定义了 JUploadUserInfo 类
*/

/*!
	\class JUploadUserInfo juploaduserinfo.h
	\ingroup client
	\brief 修改用户信息
*/

using namespace NetworkData;

JUploadUserInfo::JUploadUserInfo(QObject *parent) :
    JInformationSendBase(parent)
{
}

JCode JUploadUserInfo::pushUserInfo(const JUserInfo& userinfo,int msecs)
{
	return pushInformationData(userinfo.getUserId(),userinfo.toByteArray(),msecs);
}

NetworkData::JHead JUploadUserInfo::getHead(JID id)const
{
	return JUserInfo(id).head();
}
