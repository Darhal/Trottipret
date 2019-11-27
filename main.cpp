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

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();*/
    qInfo(QDir::currentPath().toLocal8Bit().constData());
    DatabaseManager::GetInstance().Exec("create table if not exists person "
                                                      "(id integer primary key, "
                                                      "name varchar(20), "
                                                      "age integer)");
    DatabaseManager::GetInstance().Exec("INSERT INTO person (id, name, age) "
                                       "VALUES (%d, '%s', %d)", 1, "Omar", 21);
    QSqlQuery r = DatabaseManager::GetInstance().Exec("SELECT * from person");
    r.next();
    qInfo("ID: %d | Name: %s | Age: %d\n", r.value(0).toInt(),
          r.value(1).toString().toLocal8Bit().constData(),
          r.value(2).toInt());
    //return a.exec();
}
