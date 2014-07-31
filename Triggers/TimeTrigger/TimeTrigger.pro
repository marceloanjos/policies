QT       += core

TEMPLATE = lib
TARGET = TimeTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${TRIGGERDIR})

HEADERS += \
    timetrigger.h

SOURCES += \
    timetrigger.cpp

