#ifndef JSQLINVITATIONCODEDB_H
#define JSQLINVITATIONCODEDB_H

#include "../jabstractinvitationcodedb.h"

class JSQLInvitationCodeDB : public JAbstractInvitationCodeDB
{
public:
    explicit JSQLInvitationCodeDB(QObject *parent = 0);
	int removeInvitationCode(const QString& code);
	JCode addInvitationCode(const QString& code);
};

#endif // JSQLINVITATIONCODEDB_H
