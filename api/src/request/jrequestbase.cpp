#include "jrequestbase.h"

/*!
	\file jrequestbase.h
	\brief 定义了 JRequestBase 类
*/

/*!
	\class JRequestBase jrequestbase.h "service/jrequestbase.h"
	\ingroup client
	\brief 向服务器发送请求的基类。
*/

JRequestBase::JRequestBase(QObject *parent)
	:QObject(parent)
{
}
