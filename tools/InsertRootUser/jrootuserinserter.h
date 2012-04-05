#ifndef JROOTUSERINSERTER_H
#define JROOTUSERINSERTER_H

#include <QString>

class JRootUserInserter
{
public:
	bool insert(const QString& password);
	const QString& errorString()const;
private:
	QString m_error ;
};

#endif // JROOTUSERINSERTER_H

