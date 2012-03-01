#include "jinvitationcode.h"

#include "database/jabstractdatabasefactory.h"

#include <QDebug>

JInvitationCode::JInvitationCode()
{
}

bool JInvitationCode::checkInvitationCode(const QString& invitationCode)
{
	JAbstractInvitationCodeDB *db =
		JAbstractDatabaseFactory::getInstance()->getInvitationCodeDB();
	int rm = db->removeInvitationCode(invitationCode) ;
	qDebug()<<__FUNCTION__<<rm;
	return rm == 1;
}
