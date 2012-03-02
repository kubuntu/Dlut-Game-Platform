#include "juploadinvitationcode.h"

#include <QDataStream>

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
