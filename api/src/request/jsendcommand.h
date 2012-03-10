#ifndef JSENDCOMMAND_H
#define JSENDCOMMAND_H

#include "jrequestbase.h"
#include "../global/jglobal.h"

class JClientCommandProcessor;

class JSendCommand : public JRequestBase
{
    Q_OBJECT
public:
    explicit JSendCommand(QObject *parent = 0);
	void sendShutdown();
	void sendRestart();
signals:
	void receiveCommandResult(JID type,JCode result);
private:
	JClientCommandProcessor* m_processor;
};

#endif // JSENDCOMMAND_H
