QT       += core

TEMPLATE = lib
TARGET = ActionTemplate
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    actiontemplate.h

SOURCES += \
    actiontemplate.cpp

