TEMPLATE  = subdirs
SUBDIRS = \
    package \
    api \
    MainClient \
    MainServer \
    SnakeClient \
    SnakeServer \
    CreateDatabase
SUBDIRS += tools
MainClient.depends = api
MainClient.depends = package
MainServer.depends = api
SnakeClient.depends = api
SnakeServer.depends = api
