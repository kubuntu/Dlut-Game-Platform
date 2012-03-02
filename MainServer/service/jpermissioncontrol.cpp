#include "jpermissioncontrol.h"

#include <Information/JHead>
#include <Information/JInformation>
#include <Global/Login>
#include <Global/Command>

#include "../database/jabstractdatabasefactory.h"

using namespace NetworkData;

JPermissionControl::JPermissionControl(JID userId)
	:m_userId(userId)
{
	m_dbFactory=JAbstractDatabaseFactory::getInstance();
}

bool JPermissionControl::checkInformation(JID protocol,const JHead& head)
{
	switch(protocol){
	case EIP_DownloadRemoteMtime:
		switch(head.m_type){
		case EIT_UserInfo:
		case EIT_GameInfo:
		case EIT_ServerInfo:
			return (m_userId > 0);
			break;
		default:
			return false;
			break;
		}
		break;
	case EIP_DownloadData:
		switch(head.m_type){
		case EIT_UserInfo:
		case EIT_GameInfo:
		case EIT_ServerInfo:
			return (m_userId > 0);
			break;
		default:
			return false;
			break;
		}
		break;
	case EIP_UploadData:
		switch(head.m_type){
		case EIT_UserInfo://只有自己和Admin可以更改用户信息
			if(head.m_id == m_userId) return true;
			{
				JAbstractLoginDB* logindb=m_dbFactory->getLoginDB();
				if(logindb->checkRole(m_userId,ROLE_ADMIN)) return true;
			}
			return false;
			break;
		case EIT_GameInfo://只有游戏运营者和Admin可以更改游戏信息
			{
				JAbstractLoginDB* logindb=m_dbFactory->getLoginDB();
				if(logindb->checkRole(m_userId,ROLE_ADMIN)) return true;
				JID gameId = head.m_id;
				JAbstractGameInfoDB* gameinfoDb=m_dbFactory->getGameInfoDB();
				JGameInfo gameinfo = gameinfoDb->getGameInfoById(gameId);
				return gameinfo.getRunner() == m_userId;
			}
			break;
		case EIT_ServerInfo://只有游戏运营者和Admin可以更改游戏信息
			{
				JAbstractLoginDB* logindb=m_dbFactory->getLoginDB();
				if(logindb->checkRole(m_userId,ROLE_ADMIN)) return true;
				JID serverId = head.m_id;
				JAbstractServerInfoDB* serverinfoDB = m_dbFactory->getServerInfoDB();
				JServerInfo serverinfo = serverinfoDB->getServerInfoById(serverId);
				return serverinfo.getRunner() == m_userId;
			}
			break;
		case EIT_InvitationCode:// 只有Admin可以添加邀请码
			{
				JAbstractLoginDB* logindb=m_dbFactory->getLoginDB();
				if(logindb->checkRole(m_userId,ROLE_ADMIN)) return true;
				return false;
			}
			break;
		}
		break;
	default:
		return false;
	}
	return false;
}

bool JPermissionControl::checkCommand(JID type,JID)
{
	switch(type){
	case ECT_Shutdown:
	case ECT_Restart:
		{
			JAbstractLoginDB* logindb=m_dbFactory->getLoginDB();
			if(logindb->checkRole(m_userId,ROLE_ROOT)) return true;
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}

bool JPermissionControl::checkControlRole(JID,ERole targetRole,EControlRoleAction)
{
	JAbstractLoginDB* logindb=m_dbFactory->getLoginDB();
	JID testRole;
	for(testRole = targetRole+1;testRole <= ROLE_ROOT;++testRole){
		if(logindb->checkRole(m_userId,(ERole)testRole)){
			return true;
		}
	}
	return false;
}

bool JPermissionControl::isMultiLoginAble(ERole role)
{
	return role == ROLE_GAMESERVERRUNNER;
}

bool JPermissionControl::canChangePassword(JID toUserId)
{
	if( m_userId == toUserId ){ // 自己可以
		return true ;
	}else{
		JAbstractLoginDB* logindb=m_dbFactory->getLoginDB();
		if(logindb->checkRole(m_userId,ROLE_ADMIN)) return true; // admin 可以
		if(logindb->checkRole(m_userId,ROLE_ROOT)) return true; // root 可以
		return false;
	}
}
