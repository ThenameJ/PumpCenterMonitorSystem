DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

include(common/common.pri)
include(connections/connections.pri)
include(net/net.pri)
include(manager/manager.pri)
include(logger/logger.pri)
include(database/database.pri)


HEADERS += \
    $$PWD/server.h

SOURCES += \
    $$PWD/server.cpp


