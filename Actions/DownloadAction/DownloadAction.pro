QT       += core
QT       += network

TEMPLATE = lib
TARGET = DownloadAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

HEADERS += \
    downloadaction.h \
    downloadmanager.h

SOURCES += \
    downloadaction.cpp \
    downloadmanager.cpp

