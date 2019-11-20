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
    /* MainWindow w;
    w.show();*/
    Utilisateur user;
    OffreLocation& offre = user.ajouterOffre();
    offre.SetTrottinette(new Trottinette("XFVZ526", 12, "Bonne Etat"));
    offre.SetDateDebut(QDateTime(QDate(2019, 11, 15), QTime(12, 0, 0)));
    offre.SetDateFin(QDateTime(QDate(2019, 12, 1), QTime(12, 0, 0)));
    offre.SetLieuRetrait("Place Stan");
    offre.SetLieuRetour("Place Stan");
    offre.SetPrixCaution(15);

    qInfo() << "Utilisateur {" << user.GetIdentifiant() << "}";
    for (const OffreLocation& offre : user.GetOffreLocation()){
        qInfo() << "\tOffreLocation {" << offre.GetDateDebut() << " - " << offre.GetDateFin() << "}";
    }

    return a.exec();
}
