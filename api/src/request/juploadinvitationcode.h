#ifndef JUPLOADINVITATIONCODE_H
#define JUPLOADINVITATIONCODE_H

#include "jinformationsendbase.h"

class JUploadInvitationCode : public JInformationSendBase
{
    Q_OBJECT
public:
    explicit JUploadInvitationCode(QObject *parent = 0);
	JCode pushInvitationCode(const QString& code , int msecs = 30000);
	NetworkData::JHead getHead(JID id)const;
};

#endif // JUPLOADINVITATIONCODE_H
