QT -= gui
QT += sql

include (../libarg/arg.pri)
LIBS += -L../libarg
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../libarg

SOURCES += \
	main.cpp \
	jdbconnecter.cpp \
	jdgpdbtablecreater.cpp

HEADERS += \
	jdbconnecter.h \
	jdgpdbtablecreater.h