#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T22:11:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphEmgMyoData
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    emggrapher.cpp \
    emgrecordsparser.cpp \
    emggraphdrawer.cpp

HEADERS  += widget.h \
    emggrapher.h \
    emgrecordsparser.h \
    emggraphdrawer.h \
    gnuplot_i.hpp

FORMS    += widget.ui

CONFIG += c++11
