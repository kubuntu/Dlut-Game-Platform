TEMPLATE  = subdirs
SUBDIRS = api MainClient MainServer test_api SnakeClient SnakeServer \
    CreateDatabase package
MainClient.depends = api
MainClient.depends = package
MainServer.depends = api
test_api.depends = api
SnakeClient.depends = api
SnakeServer.depends = api
