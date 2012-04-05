#ifndef JDBCONNECTER_H
#define JDBCONNECTER_H

#include <QString>
#include <QMap>

class JDbConnecter{
public:
	bool connect(
		const QMap<QString,QString>& argumentMap
	);
	const QString& errorString()const;
private:
	QString m_error ;
};

#endif // JDBCONNECTER_H

