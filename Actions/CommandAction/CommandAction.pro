QT       += core

TEMPLATE = lib
TARGET = CommandAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    commandaction.h

SOURCES += \
    commandaction.cpp

