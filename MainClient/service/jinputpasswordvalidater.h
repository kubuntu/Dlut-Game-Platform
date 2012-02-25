#ifndef JINPUTPASSWORDVALIDATER_H
#define JINPUTPASSWORDVALIDATER_H

#include <QString>

class JInputPasswordValidater
{
public:
    JInputPasswordValidater();
	bool validatePassword(const QString& pswd);
	QString getErrorString()const;
private:
	QString m_error ;
};

#endif // JINPUTPASSWORDVALIDATER_H
