#include "jclientloginprocessor.h"

#include "jmainclientsocket.h"
#include "jsession.h"

JClientLoginProcessor::JClientLoginProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientLoginProcessor* JClientLoginProcessor::getInstance(){
    static JClientLoginProcessor* instance=NULL;
    if(NULL==instance){
		JMainClientSocket* socket=JMainClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance=new JClientLoginProcessor(session,socket);
		socket->registerProcessor(instance);
    }
    return instance;
}

void JClientLoginProcessor::login(const QString& loginname,
                                  const QString& passwd,
                                  ERole role){
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<loginname<<passwd;
    stream<<(JID)role;
	JCode code=sendData(data);
	if(0!=code){
		qDebug()<<"JClientLoginProcessor::login : sendData failed:"<<code;
	}
}

void JClientLoginProcessor::process(const QByteArray& data){
    QDataStream stream(data);
    JCode code;
    JID irole ;
	QByteArray loginhashcode;
    stream>>code;
    if(code==0)
    {
        stream>>m_userid;
		stream>>irole;
		stream>>loginhashcode;
		ERole role = (ERole)irole;
		getSession()->setUserId(m_userid);
		getSession()->setRole(role) ;
		getSession()->setLoginHashCode(loginhashcode);
    }
    emit loginCode(code);
}

JType JClientLoginProcessor::getProcessorType()const{
    return EPI_LOGIN;
}
