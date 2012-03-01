#ifndef JABSTRACTINVITATIONCODEDB_H
#define JABSTRACTINVITATIONCODEDB_H

#include <QObject>

class JAbstractInvitationCodeDB : public QObject
{
public:
	JAbstractInvitationCodeDB(QObject *parent=0):QObject(parent){}

	// return effect rows
	virtual int removeInvitationCode(const QString& code)=0;
};

#endif // JABSTRACTINVITATIONCODEDB_H
