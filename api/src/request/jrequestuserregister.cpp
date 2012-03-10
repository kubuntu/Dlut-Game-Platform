#include "jrequestuserregister.h"

#include <QCoreApplication>

#include "../network/jclientuserregisterprocessor.h"
#include "../global/jelapsedtimer.h"
#include "../global/jencryptor.h"

/*!
	\file jrequestuserregister.h
	\brief 定义了 JRequestUserRegister 类
*/

/*!
	\class JRequestUserRegister jrequestuserregister.h
	\ingroup client
	\brief 发送用户注册请求
*/

const QString registerErrorString[]={
	QObject::tr("success"),
	QObject::tr("permission denied"),
	QObject::tr("role over flow"),
	QObject::tr("login name exists"),
	QObject::tr("login name length error"),
	QObject::tr("password length error"),
	QObject::tr("invitation code error"),
	QObject::tr("user id is full"),
};

JRequestUserRegister::JRequestUserRegister(QObject *parent) :
    JRequestBase(parent)
{
	m_processor = JClientUserRegisterProcessor::getInstance();
	m_registerError = ER_SUCCESS;
	m_state = ERS_Init;
	connect(m_processor,
			SIGNAL(receiveRegisterResult(JCode,JID,QString)),
			SLOT(on_processor_receiveRegisterResult(JCode,JID,QString)));
}

void JRequestUserRegister::sendRegister(
	const QString& loginname,
	const QString& password,
	ERole role,
	const QString& invitationCode
	)
{
	m_state = ERS_Sending;
	JEncryptor e;
	m_processor->sendRegister(loginname,e.encryptPassword(password),role,invitationCode);
}

JRequestUserRegister::ERegisterState JRequestUserRegister::getRegisterState()const
{
	return m_state;
}

bool JRequestUserRegister::waitForRegisterResult(int msecs)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(getRegisterState()!=ERS_Sending)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return getRegisterState()==ERS_Success;
}

const QString& JRequestUserRegister::getRegisterError()const
{
	return registerErrorString[m_registerError];
}

void JRequestUserRegister::on_processor_receiveRegisterResult(JCode result,JID userId,const QString& loginname)
{
	switch(result){
	case 0:
		m_state=ERS_Success;
		m_registerError = ER_SUCCESS;
		break;
	default:
		m_state=ERS_Failed;
		m_registerError=(ERegister)result;
		break;
	}
	emit receiveRegisterResult(result,userId,loginname);
}
