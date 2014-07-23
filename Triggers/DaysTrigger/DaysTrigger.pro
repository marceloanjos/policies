QT       += core

TEMPLATE = lib
TARGET = DaysTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    daystrigger.h

SOURCES += \
    daystrigger.cpp

