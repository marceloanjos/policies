QT       += core

TEMPLATE = lib
TARGET = DeleteAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    deleteaction.h

SOURCES += \
    deleteaction.cpp

