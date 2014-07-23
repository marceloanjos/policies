QT       += core

TEMPLATE = lib
TARGET = MaskTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    masktrigger.h

SOURCES += \
    masktrigger.cpp

