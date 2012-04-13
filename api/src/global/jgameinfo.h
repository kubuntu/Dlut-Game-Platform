#ifndef JGAMEINFO_H
#define JGAMEINFO_H

#include "jserializabledata.h"
#include "jglobal.h"
#include "jversion.h"

#include <QString>

/*!
    \file jgameinfo.h
    \ingroup global
    \brief 定义了 JGameInfo 类
*/

class JGameInfo : public JSerializableData
{
public:
	JGameInfo(JID gameId=-1);
	JGameInfo(JID gameId,
			  const QString& name,
			  const JVersion& version,
			  JID author,
			  JID runner,
			  const QString& introduction,
			  JID serverId,
			  const QString& downloadUrl);
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head()const;

	JID getGameId()const;
	const QString& getName()const;
	const JVersion& getVersion()const;
	JID getAuthor()const;
	JID getRunner()const;
	const QString& getIntroduction()const;
	JID getServerId()const;
	const QString& getDownloadUrl()const;
private:
	QString m_name;
	JVersion m_version;
	JID m_author;
	JID m_runner;
	QString m_introduction;
	JID m_serverId;
	QString m_downloadUrl;
};

#endif // JGAMEINFO_H
