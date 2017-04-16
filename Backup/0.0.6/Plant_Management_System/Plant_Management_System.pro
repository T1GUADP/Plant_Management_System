# Qt project file - qmake uses his to generate a Makefile

QT       += core gui

CONFIG          += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlantManagementSytem

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm -lbcm2835
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm -lbcm2835

HEADERS += window.h adcreader.h gpio-sysfs.h gz_clk.h datalogger.h

SOURCES += main.cpp window.cpp adcreader.cpp gpio-sysfs.cpp gz_clk.cpp datalogger.cpp


