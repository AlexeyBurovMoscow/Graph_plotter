#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T13:41:45
#
#-------------------------------------------------

QT       += gui core
greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets printsupport
TARGET = ts
CONFIG   -= console
CONFIG   -= app_bundle
CONFIG += C++11
TEMPLATE = app
INCLUDEPATH += .

SOURCES += main.cpp \
    settings_screen.cpp \
    password_screen.cpp \
    plotters_screen.cpp \
    reports_screen.cpp \
    configurator.cpp \
    qcustomplot.cpp \
    termosensor.cpp \
    calendarwidget.cpp

HEADERS += \
    settings_screen.h \
    password_screen.h \
    plotters_screen.h \
    reports_screen.h \
    configurator.h \
    qcustomplot.h \
    termosensor.h \
    calendarwidget.h
