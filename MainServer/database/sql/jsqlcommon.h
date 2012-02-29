#ifndef JSQLCOMMON_H
#define JSQLCOMMON_H

#define PREPARE_FAILED \
	qDebug()<<__FUNCTION__<< " prepare failed : "<<query.lastError().databaseText()

#define EXEC_FAILED \
	qDebug()<<__FUNCTION__<< " exec failed : "<<query.lastError().databaseText()

#define PREPARE( query , sql , retval ) \
	if( ! query.prepare( sql ) ){ \
		PREPARE_FAILED ; \
		return retval; \
	}

#define EXEC( query , retval ) \
	if ( ! query.exec()) { \
		EXEC_FAILED ; \
		return retval ; \
	}

#endif // JSQLCOMMON_H

