#ifndef JTESTSTREAMINVITATIONCODEDB_H
#define JTESTSTREAMINVITATIONCODEDB_H

#include "../jabstractinvitationcodedb.h"

class JTestStreamInvitationCodeDB : public JAbstractInvitationCodeDB
{
public:
    explicit JTestStreamInvitationCodeDB(QObject *parent = 0);
	static void read();
	static void flush();
	int removeInvitationCode(const QString& code);
private:
	static QList<QString> s_codelist;
};

#endif // JTESTSTREAMINVITATIONCODEDB_H
