#include "juploadinvitationcode.h"

#include <QDataStream>

/*!
	\file juploadinvitationcode.h
	\brief 定义了 JUploadInvitationCode 类
*/

/*!
	\class JUploadInvitationCode juploadinvitationcode.h
	\ingroup client
	\brief 添加注册邀请码
*/

using namespace NetworkData;

JUploadInvitationCode::JUploadInvitationCode(QObject *parent) :
    JInformationSendBase(parent)
{
}

JCode JUploadInvitationCode::pushInvitationCode(
	const QString& code ,
	int msecs
){
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<code;
	return pushInformationData(
				-1,
				data,
				msecs
				);
}

NetworkData::JHead JUploadInvitationCode::getHead(JID id)const
{
	return JHead(id,EIT_InvitationCode,0);
}
