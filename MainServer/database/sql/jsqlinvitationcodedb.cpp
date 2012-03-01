#include "jsqlinvitationcodedb.h"

#include "jsqlcommon.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

#define TableName "invitationCode"

JSQLInvitationCodeDB::JSQLInvitationCodeDB(QObject *parent) :
	JAbstractInvitationCodeDB(parent)
{
}

int JSQLInvitationCodeDB::removeInvitationCode(const QString& code)
{
	QSqlQuery query;
	PREPARE( query,
			"DELETE FROM "
			TableName
			" where code = :code "
			"LIMIT 1",
			0);

	query.bindValue(":code" , code );

	EXEC( query , -1 );

	return query.numRowsAffected();
}
