QT       += core

TEMPLATE = lib
TARGET = DateTimeTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${TRIGGERDIR})

HEADERS += \
    datetimetrigger.h

SOURCES += \
    datetimetrigger.cpp

