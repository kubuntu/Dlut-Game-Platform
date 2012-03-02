#include "jinvitationcode.h"

#include "database/jabstractdatabasefactory.h"

JInvitationCode::JInvitationCode()
{
}

bool JInvitationCode::checkInvitationCode(const QString& invitationCode)
{
	JAbstractInvitationCodeDB *db =
		JAbstractDatabaseFactory::getInstance()->getInvitationCodeDB();
	int rm = db->removeInvitationCode(invitationCode) ;
	return rm == 1;
}
