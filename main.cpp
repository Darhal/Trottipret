#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QDebug>
#include "Core/applicationmanager.h"
#include <qdir.h>

/*
* Fonction principale l'exécution du programme commencera à partir d'ici
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // QApplication
    ApplicationManager& manager = ApplicationManager::GetInstance();
    manager.StartApplication();
    MainWindow w;
    w.show();
    ApplicationManager::Free();
    return a.exec(); // retourne a.exec();
}
