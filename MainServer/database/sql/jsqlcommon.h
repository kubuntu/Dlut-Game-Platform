#ifndef JSQLCOMMON_H
#define JSQLCOMMON_H

#define PREPARE_FAILED \
	qDebug()<<__FUNCTION__<< " prepare failed : "<<query.lastError().databaseText()

#define EXEC_FAILED \
	qDebug()<<__FUNCTION__<< " exec failed : "<<query.lastError().databaseText()

#endif // JSQLCOMMON_H

