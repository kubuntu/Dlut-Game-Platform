TEMPLATE  = subdirs
SUBDIRS = \
    package \
    api \
    MainClient \
    MainServer
SUBDIRS += tools
MainClient.depends = api
MainClient.depends = package
MainServer.depends = api
SnakeClient.depends = api
SnakeServer.depends = api
