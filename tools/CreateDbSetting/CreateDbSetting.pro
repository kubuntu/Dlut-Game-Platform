QT -= gui

include (../libarg/arg.pri)
LIBS += -L../libarg
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../libarg

SOURCES += \
	main.cpp \
	jdgpdbsettingcreater.cpp

HEADERS += \
	jdgpdbsettingcreater.h
