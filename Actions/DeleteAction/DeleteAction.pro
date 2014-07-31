QT       += core

TEMPLATE = lib
TARGET = DeleteAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${ACTIONDIR})

HEADERS += \
    deleteaction.h

SOURCES += \
    deleteaction.cpp

