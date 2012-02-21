#ifndef JSESSION_H
#define JSESSION_H

#include <QObject>
#include "../global/jglobal.h"
#include "../global/elogin.h"

class JSession : public QObject
{
public:
    explicit JSession(QObject *parent = 0);
	JID getUserId()const;
	void setUserId(JID userId);
	ERole getRole()const;
	void setRole(ERole role);
	const QByteArray& getLoginHashCode()const;
	void setLoginHashCode(const QByteArray& code);
	QString getLoginHashCodeStr()const;
	void setLoginHashCodeStr(const QString& str);
private:
	JID m_userId;
	ERole m_role ;
	QByteArray m_loginhashcode;
};

#endif // JSESSION_H
