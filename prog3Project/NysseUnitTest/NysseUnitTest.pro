QT += testlib
QT -= gui

TARGET = tst_statistictest.cpp

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_statistictest.cpp \
        ../Game/Core/tilasto.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Game/Core/tilasto.hh \
    ../Course/CourseLib/core/location.hh

INCLUDEPATH += \
            ../Game/ \
            ../Course/

DEPENDPATH += \
            ../Game/  \
            ../Course/
