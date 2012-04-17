#include "jlog.h"

#include "jversion.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>

JLog::JLog()
{
	// mkdir data
	QDir dir = QCoreApplication::applicationDirPath() ;
	if( !dir.exists("data") ){
		dir.mkdir("data");
	}
	
	// open file
	QString fileName = QString("data/%1_%2.log")
		.arg(QCoreApplication::applicationName())
		.arg(JVersion::platformVersion().toString());
	m_file.setFileName(fileName);
	m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text );
	m_stream.setDevice(&m_file);
	
	// write head
	stream()<<endl;
	stream()<<"=========================================="<<endl;
	stream()<<"compile time : "<<__DATE__<<' '<<__TIME__<<endl;
	stream()<<"platform version :"<<JVersion::platformVersion().toString()<<endl;
	stream()<<"run time : "<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<endl;
	stream()<<endl;
}

QTextStream& JLog::stream()
{
	return m_stream;
}

QTextStream& jLog()
{
	static JLog log;
	return log.stream();
}
