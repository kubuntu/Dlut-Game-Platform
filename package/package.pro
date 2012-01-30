TEMPLATE  = subdirs
SUBDIRS = lib testlib packager
testlib.depends = lib
packager.depends = lib
