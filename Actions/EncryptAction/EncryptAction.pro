QT       += core

TEMPLATE = lib
TARGET = EncryptAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

# THIS WILL NOT COMPILE unless you include the encryption lib

HEADERS += \
    encryptaction.h

SOURCES += \
    encryptaction.cpp

unix {
LIBS += -L$${DISTLIBDIR} -lEncryption
}

win32 {
LIBS += -L$${DISTLIBDIR} -lEncryption1
}
