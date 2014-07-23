QT       += core

TEMPLATE = lib
TARGET = CompressAction
CONFIG += plugin
VERSION = 1.0.0

#Include the config file
include($$quote(../../Interfaces/Interfaces.pri))

# THIS WILL NOT COMPILE, unless you include the zip library

INCLUDEPATH += $$quote($$LIBDIR/Zip/)
INCLUDEPATH += $$quote($$PWD)

DEPENDPATH += $$quote($$PWD)
DEPENDPATH += $$quote($$LIBDIR/Zip/)

#Set the Setination dir
DESTDIR = $$quote($${ACTIONDIR})

HEADERS += \
    compressaction.h \
    $$quote($$LIBDIR/Zip/zipreader.h)

SOURCES += \
    compressaction.cpp

#Add the libs
unix {
LIBS += -L$${DISTLIBDIR} -lZip
}

win32 {
LIBS += -L$${DISTLIBDIR} -lZip1
}
