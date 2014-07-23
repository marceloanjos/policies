QT       += core

TEMPLATE = lib
TARGET = TimeTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    timetrigger.h

SOURCES += \
    timetrigger.cpp

