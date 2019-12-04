#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QDebug>
#include "Core/utilisateur.h"
#include "Core/trottinette.h"
#include "Core/offrelocation.h"
#include "Core/proprietaire.h"
#include "Core/trottinette.h"
#include "Core/databasemanager.h"
#include <qdir.h>

/*
* Fonction principale l'exécution du programme commencera à partir d'ici
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // QApplication
    MainWindow w; // Constructeur par défaut et alloue statiquement notre MainWindow
    w.show(); // Appele son show
    return a.exec(); // retourne a.exec();
}
