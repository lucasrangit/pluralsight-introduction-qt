#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T21:38:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VFP
TEMPLATE = app

SOURCES += main.cpp \
        View/mainview.cpp \
    View/setuptab.cpp \
    startup.cpp \
    utils.cpp \
    Model/settings.cpp \
    Model/provider.cpp \
    Model/instsocket.cpp \
    Model/instrument.cpp

HEADERS  += View/mainview.h \
    View/setuptab.h \
    startup.h \
    utils.h \
    Model/settings.h \
    Model/provider.h \
    Model/instsocket.h \
    Model/instrument.h

FORMS    += View/mainview.ui \
    View/setuptab.ui

OTHER_FILES +=

RESOURCES += \
    VfpResources.qrc
