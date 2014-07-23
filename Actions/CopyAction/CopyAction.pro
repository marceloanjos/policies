QT       += core

TEMPLATE = lib
TARGET = CopyAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    copyaction.h

SOURCES += \
    copyaction.cpp

