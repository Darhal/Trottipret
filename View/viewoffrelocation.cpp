#include "viewoffrelocation.h"
#include "ui_viewoffrelocation.h"
#include <QMessageBox>
#include <Core/databasemanager.h>
#include <Core/applicationmanager.h>
#include <qdebug.h>

// Constructeur
ViewOffreLocation::ViewOffreLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewOffreLocation)
{
    ui->setupUi(this);
}

bool ViewOffreLocation::VerifyData()
{
    // qDebug() << ApplicationManager::GetInstance().GetCurrentUser() << " - " << NULL;
    if (ApplicationManager::GetInstance().GetCurrentUser() == NULL){
        ui->warning->setText("Cette fonction n'est pas disponible lorsque vous n'êtes pas connecté.");
        return false;
    }

    QString ref = ui->ref->text();
    QSqlQuery& res = DatabaseManager::GetInstance().Exec("SELECT * FROM offrelocation WHERE ref_trotti = %s", ref.toLocal8Bit().constData());

    if (res.next()){ // Il ya des resultats alors return false et print l'error
        ui->warning->setText("La référence de la trottinette existe déjà dans la base de données.");
        return false;
    }

    return true;
}

void ViewOffreLocation::SubmitOffre()
{
    QString ref = ui->ref->text();
    QString model = ui->model->text();
    QString etat = ui->etat->currentData().toString();
    QString date_debut = ui->date_retrait->text();
    QString date_fin = ui->date_retour->text();
    QString lieu_debut = ui->lieu_retrait->text();
    QString lieu_fin = ui->lieu_retour->text();
    float prix_caution = ui->prix_caution->text().toDouble();

    DatabaseManager::GetInstance().
        Exec(
                "INSERT INTO trottinettes (ref_trotti, model, etat)"
                "VALUES ('%s', '%s', '%s');",
                ref.toLocal8Bit().constData(),
                model.toLocal8Bit().constData(),
                etat.toLocal8Bit().constData()
        );

    DatabaseManager::GetInstance().
        Exec(
                "INSERT INTO offrelocations (date_debut, date_fin, lieu_debut, lieu_fin, prix_caution, identifiant, ref_trotti)"
                "VALUES ('%s', '%s', '%s', '%s', '%f', '%s', '%s');",
                date_debut.toLocal8Bit().constData(),
                date_fin.toLocal8Bit().constData(),
                lieu_debut.toLocal8Bit().constData(),
                lieu_fin.toLocal8Bit().constData(),
                prix_caution,
                ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant().toLocal8Bit().constData(),
                ref.toLocal8Bit().constData()
        );

    // Petite fenêtre pour informer l'utilisateur que tout va bien
    QMessageBox::information(
        this,
        tr("Offre location est soumis"),
        QString("L'offre est soumise avec succès. Si vous voulez voir toutes vos offres visitez mes offres de locations.")
    );

    QDialog::accept(); // fermer la fenêtre de dialog
}

void ViewOffreLocation::accept()
{
    if (this->VerifyData()){
        this->SubmitOffre();
    }
}

// Destructeur
ViewOffreLocation::~ViewOffreLocation()
{
    delete ui;
}
