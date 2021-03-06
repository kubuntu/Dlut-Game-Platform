#ifndef JUSERINFO_H
#define JUSERINFO_H

#include <QString>

#include "jserializabledata.h"
#include "jglobal.h"

/*!
    \file juserinfo.h
    \ingroup global
    \brief 定义了 JUserInfo 类
*/

class JUserInfo : public JSerializableData{
public:
	JUserInfo(JID id=-1,
		  const QString& name=QString(),
		  const QString& org=QString());
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head()const;

	JID getUserId()const;
	const QString& getNickname()const;
	const QString& getOrganization()const;
private:
	QString m_nickname;
	QString m_organization;
};

#endif // JUSERINFO_H
