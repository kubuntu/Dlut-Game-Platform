#ifndef JINVITATIONCODE_H
#define JINVITATIONCODE_H

class QString;

class JInvitationCode
{
public:
    JInvitationCode();
	bool checkInvitationCode(const QString& invitationCode);
};

#endif // JINVITATIONCODE_H
