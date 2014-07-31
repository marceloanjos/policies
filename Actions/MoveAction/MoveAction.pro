QT       += core

TEMPLATE = lib
TARGET = MoveAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${ACTIONDIR})

HEADERS += \
    moveaction.h

SOURCES += \
    moveaction.cpp

