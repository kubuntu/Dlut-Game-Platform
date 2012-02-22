#ifndef JCHANGEPASSWORD_H
#define JCHANGEPASSWORD_H

#include <Global/Global>

class QString;

class JChangePassword
{
public:
    JChangePassword();
	JCode changePassword(
		JID userId,
		const QString& oldPassword,
		const QString& newPassword);
};

#endif // JCHANGEPASSWORD_H
