#include "jsendcommand.h"

#include "../network/jclientcommandprocessor.h"

/*!
	\file jsendcommand.h
	\brief 定义了 JSendCommand 类
*/

/*!
	\class JSendCommand jsendcommand.h
	\ingroup client
	\brief 管理员向 MainServer发送命令
	
	目前仅包括关闭和重启
*/

JSendCommand::JSendCommand(QObject *parent) :
    JRequestBase(parent)
{
	m_processor = JClientCommandProcessor::getInstance();
	connect(m_processor,
			SIGNAL(receiveCommandResult(JID,JCode)),
			SIGNAL(receiveCommandResult(JID,JCode)));
}

void JSendCommand::sendShutdown()
{
	m_processor->sendCommand(ECT_Shutdown);
}

void JSendCommand::sendRestart()
{
	m_processor->sendCommand(ECT_Restart);
}
