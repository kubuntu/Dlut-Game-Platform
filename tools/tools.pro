TEMPLATE  = subdirs
SUBDIRS = \
	libarg \
	libdbconnecter \
	CreateDbTable \
	CreateDbSetting \
	InsertRootUser
libarg.file = libarg/arg.pro
libdbconnecter.file = libdbconnecter/dbconnecter.pro
CreateDbTable.depends = libarg libdbconnecter
CreateDbSetting.depends = libarg
InsertRootUser.depends = libarg libdbconnecter
