#ifndef JCLIENTCHANGEPASSWORDPROCESSOR_H
#define JCLIENTCHANGEPASSWORDPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

class JClientChangePasswordProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
public:
	static JClientChangePasswordProcessor* getInstance() ;
	void changePassword(
			JID userId,
			const QString& encryptedOldPswd,
			const QString& encryptedNewPswd
		);
signals:
	void receiveResult(JCode code);
protected:
	void process(const QByteArray& data);
	JType getProcessorType()const;
private:
	explicit JClientChangePasswordProcessor(JSession* session,JSocketBase *socket);
};

#endif // JCLIENTCHANGEPASSWORDPROCESSOR_H
