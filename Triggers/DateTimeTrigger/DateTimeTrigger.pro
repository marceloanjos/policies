QT       += core

TEMPLATE = lib
TARGET = DateTimeTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    datetimetrigger.h

SOURCES += \
    datetimetrigger.cpp

