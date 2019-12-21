#include "viewoffrelocation.h"
#include "ui_viewoffrelocation.h"
#include <QMessageBox>
#include <Core/databasemanager.h>
#include <Core/applicationmanager.h>
#include <qdebug.h>
#include <QFileDialog>
#include <View/viewlistetrottinette.h>

// Constructeur
ViewOffreLocation::ViewOffreLocation(const QString& ref_trotti, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewOffreLocation),
    m_RefTrotti(ref_trotti)
{
    ui->setupUi(this);
}

bool ViewOffreLocation::VerifyData()
{
    if (ApplicationManager::GetInstance().GetCurrentUser() == NULL){
        ui->warning->setText("Cette fonction n'est pas disponible lorsque vous n'êtes pas connecté.");
        return false;
    }

    QSqlQuery& res = DatabaseManager::GetInstance().Exec("SELECT * FROM locations WHERE ref_trotti = %s", m_RefTrotti.toLocal8Bit().constData());

    if (res.next()){ // Il ya des resultats alors return false et print l'error
        ui->warning->setText("La référence de la trottinette existe \ndéjà dans la base de données.");
        return false;
    }

    return true;
}

void ViewOffreLocation::SubmitOffre()
{
    QString date_debut = ui->date_retrait->text();
    QString date_fin = ui->date_retour->text();
    QString lieu_debut = ui->lieu_retrait->text();
    QString lieu_fin = ui->lieu_retour->text();
    float prix_caution = ui->prix_caution->text().toDouble();

    DatabaseManager::GetInstance().
        Exec(
                "INSERT INTO locations (identifiant, ref_trotti, date_debut, date_fin, lieu_debut, lieu_fin, prix_caution, locataire)"
                "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', %f, NULL);",
                ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant().toLocal8Bit().constData(),
                m_RefTrotti.toLocal8Bit().constData(),
                date_debut.toLocal8Bit().constData(),
                date_fin.toLocal8Bit().constData(),
                lieu_debut.toLocal8Bit().constData(),
                lieu_fin.toLocal8Bit().constData(),
                prix_caution
        );

    // Petite fenêtre pour informer l'utilisateur que tout va bien
    QMessageBox::information(
        this,
        tr("Offre location est soumis"),
        QString("L'offre est soumise avec succès. Si vous voulez voir toutes vos offres visitez mes offres de locations.")
    );

    ((ViewListeTrottinette*)parent())->RefreshList();
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
