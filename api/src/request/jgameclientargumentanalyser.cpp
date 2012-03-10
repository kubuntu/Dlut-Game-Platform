#include "jgameclientargumentanalyser.h"

#include <QStringList>

/*!
	\file jgameclientargumentanalyser.h
	\brief 定义了 JGameClientArgumentAnalyser 类
*/

/*!
	\class JGameClientArgumentAnalyser jgameclientargumentanalyser.h <Helper/JGameClientArgumentAnalyser>
	\ingroup gameclient
	\brief 帮助 GameClient 分析命令行参数
	
	MainClient 向 GameClient 通过命令行参数传值。
	参数格式相对固定，可以提供一个类帮助分析。
*/

/*!
	\breif 单例方法
	
	出于性能考虑，这个类设计成单例。
*/
JGameClientArgumentAnalyser* JGameClientArgumentAnalyser::getInstance()
{
    static JGameClientArgumentAnalyser instance;
    return &instance;
}

/*!
	\brief 处理参数
	
	\return 表示分析是否成功
*/

bool JGameClientArgumentAnalyser::processArgument(const QStringList& arguments)
{
    if(arguments.length()<7){
        return false;
    }
    m_userId=arguments.at(1).toInt();
    QString strcrypro=arguments.at(2);
    m_loginhashcode=QByteArray::fromHex(strcrypro.toAscii());
    QHostAddress ms_addr(arguments.at(3));
    quint16 ms_port(arguments.at(4).toInt());
    m_mainserver = SHost(ms_addr,ms_port);
    m_gameserver = SHost(QHostAddress(arguments.at(5)),arguments.at(6).toInt());
    return true;
}

/*!
	\brief 获得用户ID
*/
JID JGameClientArgumentAnalyser::getUserId()const
{
    return m_userId;
}

/*!
	\brief 获得 LoginHashCode
	
	\sa JSession
*/
const QByteArray& JGameClientArgumentAnalyser::getLoginHashCode()const
{
    return m_loginhashcode;
}

/*!
	\brief 获得表示 MainServer 的 SHost 对象
*/
const SHost& JGameClientArgumentAnalyser::getMainServer()const
{
    return m_mainserver;
}

/*!
	\brief 获得表示 GameServer 的 SHost 对象
*/
const SHost& JGameClientArgumentAnalyser::getGameServer()const
{
    return m_gameserver;
}

JGameClientArgumentAnalyser::JGameClientArgumentAnalyser()
{
}
