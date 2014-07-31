QT       += core

TEMPLATE = lib
TARGET = DateTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${TRIGGERDIR})

HEADERS += \
    datetrigger.h

SOURCES += \
    datetrigger.cpp

