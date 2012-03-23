#ifndef JARGUMENTANALYZER_H
#define JARGUMENTANALYZER_H

#include <QMap>
#include <QStringList>

class JArgumentAnalyzer{
public:
	bool analyse() ;
	QString value(
		const QString& key,
		const QString& defaultValue=QString()
	)const;
	bool hasValue(const QString& key)const;
	const QString& errorString()const;
private:
	bool analyseStringList(const QStringList& sl);
	
	QMap<QString,QString> m_values ;
	QString m_error ;
};

#endif // JARGUMENTANALYZER_H

