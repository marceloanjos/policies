QT       += core

TEMPLATE = lib
TARGET = ActionTemplate
CONFIG += plugin
VERSION = 1.0.0

#Include the config file
include($$quote(../../Interfaces/Interfaces.pri))

#THIS WILL NOT COMPILE unless you include the encryption lib

HEADERS += \
    decryptaction.h

SOURCES += \
    decryptaction.cpp

unix {
LIBS += -L$${DISTLIBDIR} -lEncryption
}

win32 {
LIBS += -L$${DISTLIBDIR} -lEncryption1
}
