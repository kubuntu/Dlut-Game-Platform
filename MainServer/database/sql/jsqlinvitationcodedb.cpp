#include "jsqlinvitationcodedb.h"

#include "jsqlcommon.h"

#include <Global/CodeError>

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

JCode JSQLInvitationCodeDB::addInvitationCode(const QString& code)
{
	QSqlQuery query;
	PREPARE( query ,
			"INSERT INTO "
			TableName
			" (code) "
			" values ( :code )",
			EPrepareFailed
			);

	query.bindValue(":code" , code );

	EXEC( query , EExecFailed);

	return 0;
}
