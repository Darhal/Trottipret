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

SUBDIRS += \
    Trottipret.pro

FORMS += \
    mainwindow.ui \
    View/viewaddtrottinette.ui \
    View/viewalloffre.ui \
    View/viewconnection.ui \
    View/viewinscription.ui \
    View/viewlisteoffre.ui \
    View/viewlistetrottinette.ui \
    View/viewlistoffrelocation.ui \
    View/viewlocations.ui \
    View/viewmyprofile.ui \
    View/viewoffrelocation.ui

HEADERS += \
    Core/applicationmanager.h \
    Core/databasemanager.h \
    Core/locationmanager.h \
    Core/offrelocation.h \
    Core/proprietaire.h \
    Core/trottinette.h \
    Core/utilisateur.h \
    View/viewaddtrottinette.h \
    View/viewalloffre.h \
    View/viewconnection.h \
    View/viewinscription.h \
    View/viewlisteoffre.h \
    View/viewlistetrottinette.h \
    View/viewlistoffrelocation.h \
    View/viewlocations.h \
    View/viewmyprofile.h \
    View/viewoffrelocation.h \
    mainwindow.h

SOURCES += \
    Core/applicationmanager.cpp \
    Core/databasemanager.cpp \
    Core/locationmanager.cpp \
    Core/offrelocation.cpp \
    Core/proprietaire.cpp \
    Core/trottinette.cpp \
    Core/utilisateur.cpp \
    View/viewaddtrottinette.cpp \
    View/viewalloffre.cpp \
    View/viewconnection.cpp \
    View/viewinscription.cpp \
    View/viewlisteoffre.cpp \
    View/viewlistetrottinette.cpp \
    View/viewlistoffrelocation.cpp \
    View/viewlocations.cpp \
    View/viewmyprofile.cpp \
    View/viewoffrelocation.cpp \
    main.cpp \
    mainwindow.cpp

RESOURCES += \
    Assets/resources.qrc
