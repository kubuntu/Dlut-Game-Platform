#ifndef JARGUMENTANALYZER_H
#define JARGUMENTANALYZER_H

#include <QMap>
#include <QStringList>

class JArgumentAnalyzer{
public:
	bool analyse() ;
	const QString& errorString()const;
	const QMap<QString,QString>& argumentMap()const;
private:
	bool analyseStringList(const QStringList& sl);
	
	QMap<QString,QString> m_values ;
	QString m_error ;
};

#endif // JARGUMENTANALYZER_H

