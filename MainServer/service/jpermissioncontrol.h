#ifndef JPERMISSIONCONTROL_H
#define JPERMISSIONCONTROL_H

#include <Global/Global>
#include <Global/Login>

namespace NetworkData{
	class JHead;
}
class JAbstractDatabaseFactory;

class JPermissionControl
{
public:
	JPermissionControl(JID userId);
	bool checkInformation(JID protocol,const NetworkData::JHead& head);
	bool checkCommand(JID type,JID param);
	bool checkControlRole(JID targetUserId,ERole targetRole,EControlRoleAction act);
	bool isMultiLoginAble(ERole role);
	bool canChangePassword(JID toUserId);
private:
	JID m_userId;
	JAbstractDatabaseFactory* m_dbFactory;
};

#endif // JPERMISSIONCONTROL_H
