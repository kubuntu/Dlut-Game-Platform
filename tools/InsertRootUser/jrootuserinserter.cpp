#include "jrootuserinserter.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#define PREPARE_FAILED \
	m_error = QString("%1 prepare failed : %2").arg(__FUNCTION__).arg(query.lastError().databaseText())

#define EXEC_FAILED \
	m_error = QString("%1 exec failed : %2").arg(__FUNCTION__).arg(query.lastError().databaseText())

#define PREPARE( query , sql , retval ) \
	if( ! query.prepare( sql ) ){ \
		PREPARE_FAILED ; \
		return false; \
	}

#define EXEC( query , retval ) \
	if ( ! query.exec()) { \
		EXEC_FAILED ; \
		return false ; \
	}


/*!
	\file jrootuserinserter.h
	\brief 定义了 JRootUserInserter 类
*/

/*!
	\class JRootUserInserter jrootuserinserter.h "JRootUserInserter"
	\brief 向数据库内插入 root 用户
	
	命令行工具的一部分。\n
	调用 insert() 函数插入 root 用户。\n
	调用 errorString() 函数返回插入过程中发生的错误。
*/

/*!
	\brief 插入 root 用户
	
	参数 \a password 是 root 用户的密码。\n
	成功返回 true ， 失败返回 false 。
*/
bool JRootUserInserter::insert(const QString& password){
	QSqlQuery query ;
	PREPARE( query , 
			"INSERT INTO logininfo "
			"(user_name, passwd, roles) "
			"VALUES(:loginName, :passwd, :roles)" ,
			EPrepareFailed );
	
	query.bindValue(":loginName", "root");
	query.bindValue(":passwd", password);
	query.bindValue(":roles", 31);
	
	EXEC( query , EExecFailed );
	return true;
}

/*!
	\brief 返回错误字符串
*/
const QString& JRootUserInserter::errorString()const{
	return m_error;
}
