QT       += core

TEMPLATE = lib
TARGET = MaskTrigger
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${TRIGGERDIR})

HEADERS += \
    masktrigger.h

SOURCES += \
    masktrigger.cpp

