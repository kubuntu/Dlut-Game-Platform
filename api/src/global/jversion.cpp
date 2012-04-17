#include "jversion.h"

#include <QDataStream>
#include <QRegExp>
#include <QStringList>

/*!
	\class JVersion jversion.h <DataStruct/JVersion>
	\ingroup global
	\brief 管理版本号。
	
	一个版本号应包含四部分：\<主版本号\>.\<次版本号\>.\<发布号\>-\<开发号\>
	每一部分应该是一个不大于255的整数。因此版本号可以保存在一个\c quint32 类型中。
*/

/*!
	\brief 以\a data 构造一个版本号。
	
	默认将构造一个空版本号。
	\sa isNull()
*/
JVersion::JVersion(quint32 data)
{
	m_data=data;
}

/*!
	\brief 判断当前版本号是否为空。
	
	如果保存的数据等于0xFFFFFFFF，则为空。
*/
bool JVersion::isNull()const
{
	return m_data == 0xFFFFFFFF;
}

/*!
	如果当前版本号低于\a b ，返回true；否则返回false。
*/
bool JVersion::operator<(const JVersion& b)const
{
	return m_data < b.m_data;
}

/*!
	如果当前版本号高于\a b ，返回true；否则返回false。
*/
bool JVersion::operator>(const JVersion& b)const
{
	return m_data > b.m_data;
}

/*!
	如果当前版本号等于\a b ，返回true；否则返回false。
*/
bool JVersion::operator==(const JVersion& b)const
{
	return m_data == b.m_data;
}

/*!
	如果当前版本号不等于\a b ，返回true；否则返回false。
*/
bool JVersion::operator!=(const JVersion& b)const
{
	return m_data != b.m_data;
}

/*!
	\brief 直接获取内部保存的\c quint32 值。
*/
quint32 JVersion::getData()const
{
	return m_data;
}

/*!
	\brief 转化为字符串
*/
QString JVersion::toString()const
{
	return QString("%1.%2.%3.%4")
			.arg( m_data >> 24 )
			.arg( ( m_data >> 16 ) % 256 )
			.arg( ( m_data >> 8 ) % 256 )
			.arg( ( m_data >> 0 ) % 256 );
}

/*!
	\brief 从字符串构造一个 JVersion 对象
*/
JVersion JVersion::fromString(const QString& str)
{
	QRegExp reg("(\\d+)\\.(\\d+)(\\.(\\d+))?(\\.(\\d+))?");
	if(reg.exactMatch(str)){
		QStringList capTxt = reg.capturedTexts();
		quint32 data = 0;
		data = ( (capTxt.at(1).toInt() % 256) << 24 )
				+( (capTxt.at(2).toInt() % 256) << 16 )
				+( (capTxt.at(4).toInt() % 256) << 8 )
				+( (capTxt.at(6).toInt() % 256) << 0 );
		return JVersion(data);
	}else{
	}
	return JVersion();
}

#define STR(a) _STR(a)
#define _STR(a) #a
JVersion JVersion::platformVersion()
{
	QString fv = QString("%1.%2").arg( STR(VERSION) ).arg( STR(COMPILE_VERSION ) );
	return fromString(fv);
}

/*!
	\relates JVersion
	\brief 将版本号\a ver 输出到\a stream 流中。
	
	格式：32位无符号整数。
*/
QDataStream& operator<<(QDataStream& stream,const JVersion& ver)
{
	stream<<ver.m_data;
	return stream;
}

/*!
	\relates JVersion
	\brief 从\a stream 流中读出版本号到\a ver 中。
	
	格式：32位无符号整数。
*/
QDataStream& operator>>(QDataStream& stream,JVersion& ver)
{
	stream>>ver.m_data;
	return stream;
}
