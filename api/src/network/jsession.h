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
	const QString& getLoginHashCode()const;
	void setLoginHashCode(const QString& str);
private:
	JID m_userId;
	ERole m_role ;
	QString m_loginhashcode;
};

#endif // JSESSION_H
