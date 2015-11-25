TEMPLATE = app
TARGET = ClienteQt_Fits
DEPENDPATH += .
INCLUDEPATH += .
QT += network

# Input
HEADERS += clienteqt_fits.h
SOURCES += clienteqt_fits.cpp \
           main.cpp
QT       += core gui widgets

LIBS += -L. \
        -lcfitsio \
        -lm \
        -lnsl \
