TEMPLATE  = subdirs
SUBDIRS = api MainClient MainServer SnakeClient SnakeServer \
    CreateDatabase package
MainClient.depends = api
MainClient.depends = package
MainServer.depends = api
SnakeClient.depends = api
SnakeServer.depends = api
