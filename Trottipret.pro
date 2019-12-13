#-------------------------------------------------
#
# Project created by QtCreator 2019-11-15T10:40:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Trottipret
TEMPLATE = app
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    mainwindow.cpp \
    Core/proprietaire.cpp \
    Core/offrelocation.cpp \
    Core/utilisateur.cpp \
    Core/trottinette.cpp \
    Core/locationmanager.cpp \
    View/viewoffrelocation.cpp \
    View/viewinscription.cpp \
    Core/databasemanager.cpp \
    View/viewconnection.cpp \
    Core/applicationmanager.cpp \
    View/viewlistoffrelocation.cpp \
    View/viewlistetrottinette.cpp \
    View/viewalloffre.cpp

HEADERS += \
        mainwindow.h \
    Core/proprietaire.h \
    Core/offrelocation.h \
    Core/utilisateur.h \
    Core/trottinette.h \
    Core/locationmanager.h \
    View/viewoffrelocation.h \
    View/viewinscription.h \
    Core/databasemanager.h \
    View/viewconnection.h \
    Core/applicationmanager.h \
    View/viewlistoffrelocation.h \
    View/viewlistetrottinette.h \
    View/viewalloffre.h

FORMS += \
        mainwindow.ui \
    View/viewoffrelocation.ui \
    View/viewinscription.ui \
    View/viewconnection.ui \
    View/viewlistoffrelocation.ui \
    View/viewlistetrottinette.ui \
    View/viewalloffre.ui
