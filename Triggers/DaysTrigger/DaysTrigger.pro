QT       += core

TEMPLATE = lib
TARGET = DaysTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${TRIGGERDIR})

HEADERS += \
    daystrigger.h

SOURCES += \
    daystrigger.cpp

