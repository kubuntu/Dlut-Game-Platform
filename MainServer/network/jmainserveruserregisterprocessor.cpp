#include "jmainserveruserregisterprocessor.h"
#include "../service/juserregister.h"

#include <QDataStream>
#include <Global/Login>
#include <Global/CodeError>
#include <Session/JSession>
#include <Global/Register>

JMainServerUserRegisterProcessor::JMainServerUserRegisterProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerUserRegisterProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString loginname;
	QString password;
	JID role;
	QString invitationCode;
	stream>>loginname;
	stream>>password;
	stream>>role;
	stream>>invitationCode;
	processUserRegister(loginname,password,role,invitationCode);
}

JType JMainServerUserRegisterProcessor::getProcessorType()const
{
	return EPI_UserRegister;
}

void JMainServerUserRegisterProcessor::replyRegisterResult(JCode result,JID userId,const QString& loginname)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<result;
	outstream<<userId;
	outstream<<loginname;
	sendData(outdata);
}

void JMainServerUserRegisterProcessor::processUserRegister(
	const QString& loginname,
	const QString& password,
	JID role,
	const QString& invitationCode)
{
	if(role<0 || role > ROLE_ROOT){
		replyRegisterResult(ER_RoleOverflow,-1,loginname);
		return;
	}
	JUserRegister ur(getSession()->getUserId());
	ur.execute(loginname,password,(ERole)role,invitationCode);
	replyRegisterResult(ur.getResult(),ur.getUserId(),ur.getLoginname());
}
