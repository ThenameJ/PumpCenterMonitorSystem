DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD
include(password/password.pri)


HEADERS += \
    $$PWD/departmentconfig.h \
    $$PWD/pumpconfigpage.h \
    $$PWD/systemmenuconfigwidget.h \
    $$PWD/pumpparampage.h \
    $$PWD/patientinfowin.h \
    $$PWD/basemenupage.h \
    $$PWD/baseclosemenupage.h \
    $$PWD/alarminfopage.h \
    $$PWD/onealarminfo.h \
    $$PWD/alarmvoicepage.h \
    $$PWD/historypage.h

SOURCES += \
    $$PWD/departmentconfig.cpp \
    $$PWD/pumpconfigpage.cpp \
    $$PWD/systemmenuconfigwidget.cpp \
    $$PWD/pumpparampage.cpp \
    $$PWD/patientinfowin.cpp \
    $$PWD/basemenupage.cpp \
    $$PWD/baseclosemenupage.cpp \
    $$PWD/alarminfopage.cpp \
    $$PWD/onealarminfo.cpp \
    $$PWD/alarmvoicepage.cpp \
    $$PWD/historypage.cpp
