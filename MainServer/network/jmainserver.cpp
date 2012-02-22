#include "jmainserver.h"

#include "jmainserversocket.h"
#include "jmainserverloginprocessor.h"
#include "jmainserverinformationprocessor.h"
#include "jmainservercommandprocessor.h"
#include "jmainserveruserregisterprocessor.h"
#include "jmainservercontrolroleprocessor.h"
#include "jmainserverhalltalkprocessor.h"
#include "jmainserverchangepasswordprocessor.h"
#include "jmainserversocketstrategy.h"

JMainServer::JMainServer(QObject *parent) :
    JServerBase(parent)
{
}

JServerSocketBase* JMainServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JMainServerSocket* connection = new JMainServerSocket(socket,parent);
	JSession* session = connection->getSession();
	JSocketStrategy* strategy = JMainServerSocketStrategy::getInstance();
	connection->setSocketStrategy(strategy);
	JServerNetworkDataProcessorBase* loginProcessor = new JMainServerLoginProcessor(session,connection);
	JServerNetworkDataProcessorBase* informationProcessor = new JMainServerInformationProcessor(session,connection);
	JServerNetworkDataProcessorBase* commandProcessor = new JMainServerCommandProcessor(session,connection);
	JServerNetworkDataProcessorBase* userRegisterProcessor = new JMainServerUserRegisterProcessor(session,connection);
	JServerNetworkDataProcessorBase* controlRoleProcessor = new JMainServerControlRoleProcessor(session,connection);
	JServerNetworkDataProcessorBase* hallTalkProcessor = new JMainServerHallTalkProcessor(session,connection);
	JServerNetworkDataProcessorBase* changePasswordProcessor = new JMainServerChangePasswordProcessor(session,connection);
	connection->registerProcessor(loginProcessor);
	connection->registerProcessor(informationProcessor);
	connection->registerProcessor(commandProcessor);
	connection->registerProcessor(userRegisterProcessor);
	connection->registerProcessor(controlRoleProcessor);
	connection->registerProcessor(hallTalkProcessor);
	connection->registerProcessor(changePasswordProcessor);
	return connection;
}
