QT       += core

TEMPLATE = lib
TARGET = ActionTemplate
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

#Set the Setination dir
DESTDIR = $$quote($${ACTIONDIR})

HEADERS += \
    actiontemplate.h

SOURCES += \
    actiontemplate.cpp

