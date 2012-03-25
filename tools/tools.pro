TEMPLATE  = subdirs
SUBDIRS = \
	CreateDbTable \
	libarg \
	CreateDbSetting
libarg.file = libarg/arg.pro
CreateDbTable.depends = libarg
CreateDbSetting.depends = libarg
