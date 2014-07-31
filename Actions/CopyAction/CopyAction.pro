QT       += core

TEMPLATE = lib
TARGET = CopyAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${ACTIONDIR})

HEADERS += \
    copyaction.h

SOURCES += \
    copyaction.cpp

