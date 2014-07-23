QT       += core

TEMPLATE = lib
TARGET = DecompressAction
CONFIG += plugin
VERSION = 1.0.0

include($$quote(../../Interfaces/Interfaces.pri))

# THIS WILL NOT COMPILE unless you include the zip lib

INCLUDEPATH += $$quote($$LIBDIR/Zip/)
INCLUDEPATH += $$quote($$PWD)

DEPENDPATH += $$quote($$PWD)
DEPENDPATH += $$quote($$LIBDIR/Zip/)

#Set the Setination dir
DESTDIR = $$quote($${ACTIONDIR})

HEADERS += \
    decompressaction.h \
    $$quote($$LIBDIR/Zip/zipreader.h)

SOURCES += \
    decompressaction.cpp

#Add the libs
unix {
LIBS += -L$${DISTLIBDIR} -lZip
}

win32 {
LIBS += -L$${DISTLIBDIR} -lZip1
}
