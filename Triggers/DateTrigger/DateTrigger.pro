QT       += core

TEMPLATE = lib
TARGET = DateTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    datetrigger.h

SOURCES += \
    datetrigger.cpp

