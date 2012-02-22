#include "jmainserverchangepasswordprocessor.h"

#include "service/jchangepassword.h"
#include "service/jpermissioncontrol.h"

#include <Session/JSession>
#include <Global/CodeError>

#include <QDataStream>

JMainServerChangePasswordProcessor::JMainServerChangePasswordProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerChangePasswordProcessor::process(const QByteArray& data){
	QDataStream stream(data);
	JID userId;
	QString encryptedOldPswd , encryptedNewPswd ;
	stream>>userId;
	stream>>encryptedOldPswd;
	stream>>encryptedNewPswd;

	processChangePassword(userId,encryptedOldPswd,encryptedNewPswd);
}

JType JMainServerChangePasswordProcessor::getProcessorType()const{
	return EPI_ChangePassword;
}

void JMainServerChangePasswordProcessor::processChangePassword(
	JID userId,
	const QString& oldPassword,
	const QString& newPassword
		){
	JID myUserId = getSession()->getUserId();
	JPermissionControl pc(myUserId);
	if( ! pc.canChangePassword(userId)){
		replyResult(EPermissionDenied);
	}else{
		JChangePassword cp;
		JCode code = cp.changePassword(userId,oldPassword,newPassword);
		replyResult(code);
	}
}

void JMainServerChangePasswordProcessor::replyResult(JCode code){
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<code;
	sendData(outdata);
}
