#include "jrequestlogin.h"

#include <QCoreApplication>
#include <QDebug>

#include "../network/jclientloginprocessor.h"
#include "../global/elogin.h"
#include "../global/jelapsedtimer.h"
#include "../global/jencryptor.h"

/*!
	\file jrequestlogin.h
	\brief 定义了 JRequestLogin 类
*/

/*!
	\class JRequestLogin jrequestlogin.h "service/jrequestlogin.h"
	\ingroup client
	\brief 登录请求。

	JRequestLogin对登录请求提供一个基本的封装。\n
*/

/*!
	\fn JRequestLogin::loginResult(bool result)
	\brief 登录结果

	\a result 表示是否登录成功。\n
*/

const QString loginErrorString[]={
    QObject::tr("no error"),
	QObject::tr("no such user"),
	QObject::tr("password wrong"),
	QObject::tr("no such role"),
	QObject::tr("already login"),
	QObject::tr("network error"),
};

/*!
	\brief 构造函数，没啥可说的吧？
*/
JRequestLogin::JRequestLogin(QObject *parent) :
	JRequestBase(parent)
{
    m_processor=JClientLoginProcessor::getInstance();
	m_loginError=EL_SUCCESS;
	m_state=ELS_Init;
	connect(m_processor,SIGNAL(loginCode(JCode)),SLOT(on_processor_loginCode(JCode)));
}

/*!
	\brief 发送登录请求。
	
	\a loginname 用户名。\n
	\a passwd 密码。\n
	\a role 登录身份。\n

	\sa #ERole
*/
void JRequestLogin::login(const QString& loginname,
           const QString& passwd,
           const ERole& role)
{
	m_state=ELS_Sending;
	JEncryptor e;
	m_processor->login(loginname,e.encryptPassword(passwd),role);
}

/*!
	\brief 获取当前的登录状态。

	\sa ELoginState
*/
JRequestLogin::ELoginState JRequestLogin::getLoginState()const
{
    return m_state;
}

/*!
	\brief 等待\a msecs 毫秒或收到登录结果。
	\retval true ： 登录成功。
	\retval false ： 登录失败或时间超过\a msecs 毫秒。
*/
bool JRequestLogin::waitForLogined(int msecs)
{
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
		if(getLoginState()!=ELS_Sending)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
	return getLoginState()==ELS_Success;
}

/*!
	\brief 以可读的文本返回登录错误。
*/
const QString& JRequestLogin::getLoginError()const
{
	return loginErrorString[m_loginError];
}

void JRequestLogin::on_processor_loginCode(JCode code)
{
    switch(code)
	{
    case EL_SUCCESS:
        m_state=ELS_Success;
		emit loginResult(true);
        break;
    default:
		m_state=ELS_Failed;
		m_loginError=(ELogin)code;
		emit loginResult(false);
        break;
    }
}
