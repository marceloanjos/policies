QT       += core

TEMPLATE = lib
TARGET = TriggerTemplate
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    triggertemplate.h

SOURCES += \
    triggertemplate.cpp

