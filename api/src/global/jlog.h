#ifndef JLOG_H
#define JLOG_H

#include <QFile>
#include <QTextStream>

class JLog
{
public:
	JLog();
	QTextStream& stream();
private:
	QFile m_file;
	QTextStream m_stream ;
};
QTextStream& jLog();

#endif // JLOG_H

