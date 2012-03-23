#ifndef JDBCONNECTER_H
#define JDBCONNECTER_H

#include <QString>

class JDbConnecter{
public:
	bool connect(
		const QString& drive,
		const QString& database,
		const QString& username,
		const QString& password
	);
	const QString& errorString()const;
private:
	QString m_error ;
};

#endif // JDBCONNECTER_H

