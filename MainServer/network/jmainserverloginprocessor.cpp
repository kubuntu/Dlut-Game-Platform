#include "jmainserverloginprocessor.h"

#include <QDataStream>

#include <Global/Login>
#include <Session/JSession>
#include <Socket/JSocketBase>

#include "service/jloginverification.h"
#include "service/jloginhashcodecreator.h"
#include "service/juserstatemanager.h"
#include "service/jpermissioncontrol.h"

JMainServerLoginProcessor::JMainServerLoginProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
	connect(socket,
			SIGNAL(disconnected()),
			SLOT(on_socket_disconnect()));
}

void JMainServerLoginProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString loginname;
	QString passwd;
	JID irole;
	stream>>loginname>>passwd>>irole;
	JLoginVerification lv;
	ERole role = (ERole)irole ;
	JCode code=lv.verification(loginname,passwd,role);
	if(0==code){
		JUserStateManager usm;
		JPermissionControl pc(lv.getUserId());
		if(
				usm.getUserState(lv.getUserId())!=JUserStateManager::ES_OffLine
				&& !pc.isMultiLoginAble((ERole)role)){
			code = EL_ALREADY_LOGIN;
		}else{
			JLoginHashCodeCreator lhcc;
			lhcc.setUserId(lv.getUserId());
			getSession()->setUserId(lv.getUserId());
			getSession()->setRole(role);
			getSession()->setLoginHashCode(lhcc.createLoginHashCode());
			usm.setUserState(lv.getUserId(),JUserStateManager::ES_OnLine);
		}
	}
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<code;
	if(0==code){
		outstream<<getSession()->getUserId();
		outstream<<(JID)getSession()->getRole();
		outstream<<getSession()->getLoginHashCode();
	}
	sendData(outdata);
}

JType JMainServerLoginProcessor::getProcessorType()const
{
	return EPI_LOGIN;
}

void JMainServerLoginProcessor::on_socket_disconnect()
{
	JID userId = getSession()->getUserId();
	if(userId>=0){
		JUserStateManager usm;
		usm.setUserState(userId,JUserStateManager::ES_OffLine);
	}
}
