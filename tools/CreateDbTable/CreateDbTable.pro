QT -= gui
QT += sql

TEMPLATE = app
include (../libarg/arg.pri)
include (../libdbconnecter/dbconnecter.pri)

SOURCES += \
	main.cpp \
	jdgpdbtablecreater.cpp

HEADERS += \
	jdgpdbtablecreater.h
