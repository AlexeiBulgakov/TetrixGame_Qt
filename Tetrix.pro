#-------------------------------------------------
#
# Project created by QtCreator 2019-05-02T12:39:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetrix
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        game_element.cpp \
        game_figure.cpp \
        game_filed.cpp \
        gui_tetrix_gamefield.cpp \
        gui_tetrix_gamefield_ss.cpp \
        gui_tetrix_main_window_ss.cpp \
        main.cpp \
        gui_tetrix_main_window.cpp

HEADERS += \
        game_element.h \
        game_figure.h \
        game_filed.h \
        gui_tetrix_gamefield.h \
        gui_tetrix_main_window.h \
        stdafx.h \
        tetrix_element_state.h \
        tetrix_figures.h

FORMS += \
        gui_tetrix_main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
