#-------------------------------------------------
#
# Project created by QtCreator 2013-03-01T10:57:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HexView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        maintoolbar.cpp \
        hexviewinternal.cpp \
    globalsettings.cpp \
    mainmenubar.cpp \
    fileexplorer.cpp \
    mainview.cpp \
    tabview.cpp \
    explorerwindow.cpp

HEADERS  += mainwindow.h\
            maintoolbar.h \
            hexviewinternal.h \
    globalsettings.h \
    mainmenubar.h \
    xpixmaps.h \
    fileexplorer.h \
    mainview.h \
    tabview.h \
    explorerwindow.h
