#include "jsession.h"

JSession::JSession(QObject *parent) :
    QObject(parent)
{
	m_userId=-1;
}

JID JSession::getUserId()const
{
	return m_userId;
}

void JSession::setUserId(JID userId)
{
	m_userId=userId;
}

ERole JSession::getRole()const
{
	return m_role;
}

void JSession::setRole(ERole role)
{
	m_role = role ;
}

const QString& JSession::getLoginHashCode()const
{
	return m_loginhashcode;
}

void JSession::setLoginHashCode(const QString& code)
{
	m_loginhashcode=code;
}
