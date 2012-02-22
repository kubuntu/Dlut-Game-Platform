#include "jclientchangepasswordprocessor.h"

#include "jmainclientsocket.h"
#include "jsession.h"

JClientChangePasswordProcessor
	::JClientChangePasswordProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientChangePasswordProcessor* JClientChangePasswordProcessor::getInstance(){
	static JClientChangePasswordProcessor* instance=NULL;
	if(NULL==instance){
		JMainClientSocket* socket=JMainClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance=new JClientChangePasswordProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JClientChangePasswordProcessor::changePassword(
			JID userId,
			const QString& encryptedOldPswd,
			const QString& encryptedNewPswd
		){
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<userId;
	stream<<encryptedOldPswd;
	stream<<encryptedNewPswd;
	JCode code=sendData(data);
	if(0!=code){
		qDebug()<<__FUNCTION__<<" : sendData failed:"<<code;
	}
}

void JClientChangePasswordProcessor::process(const QByteArray& data){
	QDataStream stream(data);
	JCode code;
	stream>>code;
	emit receiveResult(code);
}

JType JClientChangePasswordProcessor::getProcessorType()const{
	return EPI_ChangePassword;
}
