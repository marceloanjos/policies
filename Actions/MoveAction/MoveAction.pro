QT       += core

TEMPLATE = lib
TARGET = MoveAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    moveaction.h

SOURCES += \
    moveaction.cpp

