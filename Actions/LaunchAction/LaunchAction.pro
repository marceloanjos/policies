QT       += core

TEMPLATE = lib
TARGET = LaunchAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    launchaction.h

SOURCES += \
    launchaction.cpp

