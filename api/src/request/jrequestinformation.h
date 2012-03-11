#ifndef JREQUESTINFORMATION_H
#define JREQUESTINFORMATION_H

#include "jinformationrequestbase.h"

template <class T>
class JRequestInformation : public JInformationRequestBase
{
public:
	explicit JRequestInformation(QObject *parent = 0)
		:JInformationRequestBase(parent){}
	T pullInformation(JID Id,int msecs = 30000){
		T infor;
		infor.fromByteArray(pullInformationDataById(Id,msecs));
		return infor;
	}
	T getInformation(JID Id){
		T infor;
		infor.fromByteArray(getInformationDataById(Id));
		return infor;
	}
	NetworkData::JHead getHeadById(JID id)const{
		return T(id).head();
	}
};

#endif // JREQUESTINFORMATION_H
