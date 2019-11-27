#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include "QDebug"
#include "Core/utilisateur.h"
#include "Core/trottinette.h"
#include "Core/offrelocation.h"
#include "Core/proprietaire.h"
#include "Core/trottinette.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
