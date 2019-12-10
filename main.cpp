#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QDebug>
#include <qdir.h>

/*
* Fonction principale l'exécution du programme commencera à partir d'ici
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // QApplication
    MainWindow w;
    w.show();
    return a.exec(); // retourne a.exec();
}
