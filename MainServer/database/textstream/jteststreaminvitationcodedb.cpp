#include "jteststreaminvitationcodedb.h"

#include <QFile>
#include <QTextStream>

JTestStreamInvitationCodeDB::JTestStreamInvitationCodeDB(QObject *parent) :
    JAbstractInvitationCodeDB(parent)
{
}

QList<QString> JTestStreamInvitationCodeDB::s_codelist;

static const QString fileName = "../database/invitationCode";

void JTestStreamInvitationCodeDB::read()
{
	// clear
	s_codelist.clear();

	// open text stream
	QFile file(fileName);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream stream(&file);

	// read
	for(int i=0;i<1000;++i)
	{
		if(stream.atEnd()) break;
		QString code;
		stream>>code;
		s_codelist.push_back(code);
	}
}

void JTestStreamInvitationCodeDB::flush()
{
	if(s_codelist.isEmpty()) return;

	// open text stream
	QFile file(fileName);
	file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	QTextStream stream(&file);

	// write
	foreach(QString code , s_codelist){
		stream<<code;
		stream<<endl;
	}

	// clear
	s_codelist.clear();
}

int JTestStreamInvitationCodeDB::removeInvitationCode(const QString& code)
{
	bool bResult = s_codelist.removeOne(code);
	if(bResult){
		return 1;
	}else{
		return 0;
	}
}
