#include "jinputpasswordvalidater.h"

#include <QObject>

JInputPasswordValidater::JInputPasswordValidater()
{
}

bool JInputPasswordValidater::validatePassword(const QString& pswd)
{
	if(pswd.length()<6){
		m_error = QObject::tr("password can not be shorter than 6");
		return false;
	}
	if(pswd.length()>20){
		m_error = QObject::tr("password can not be longer than 20");
		return false;
	}
	return true;
}

QString JInputPasswordValidater::getErrorString()const
{
	return m_error ;
}
