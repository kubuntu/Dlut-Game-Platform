#ifndef EPORTSRV_H
#define EPORTSRV_H

enum EPSProtocol{EPP_LOGINHASH,EPP_PORT};
enum EServerType{
    EST_LOGIN,
    EST_GAMEINFO,
    EST_FREEPORT,
	EST_SECRETPORT,
	EST_SUBSERVER,
	EST_USERINFO,
	EST_MAX,
};

#define isInFree(type) ( EST_LOGIN==type || EST_SECRETPORT== type)

#endif // EPORTSRV_H
