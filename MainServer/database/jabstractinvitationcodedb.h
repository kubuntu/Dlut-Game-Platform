#ifndef JABSTRACTINVITATIONCODEDB_H
#define JABSTRACTINVITATIONCODEDB_H

#include <QObject>
#include <Global/Global>

class JAbstractInvitationCodeDB : public QObject
{
public:
	JAbstractInvitationCodeDB(QObject *parent=0):QObject(parent){}

	// return effect rows
	virtual int removeInvitationCode(const QString& code)=0;

	virtual JCode addInvitationCode(const QString& code)=0;
};

#endif // JABSTRACTINVITATIONCODEDB_H
