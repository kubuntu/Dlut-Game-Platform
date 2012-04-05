QT -= gui
QT += sql

include (../libarg/arg.pri)
include (../libdbconnecter/dbconnecter.pri)

LIBS += -L../libarg -L../libdbconnecter
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../libarg
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=lib/

SOURCES += \
	main.cpp \
	jrootuserinserter.cpp


HEADERS += \
	jrootuserinserter.h
