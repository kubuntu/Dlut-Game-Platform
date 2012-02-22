#ifndef JMAINSERVERCHANGEPASSWORDPROCESSOR_H
#define JMAINSERVERCHANGEPASSWORDPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JMainServerChangePasswordProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerChangePasswordProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	JType getProcessorType()const;
private:
	void processChangePassword(
		JID userId,
		const QString& oldPassword,
		const QString& newPassword
		);
	void replyResult(JCode code);
};

#endif // JMAINSERVERCHANGEPASSWORDPROCESSOR_H
