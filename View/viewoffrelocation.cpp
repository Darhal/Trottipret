#include "viewoffrelocation.h"
#include "ui_viewoffrelocation.h"
#include <QMessageBox>
#include <qdebug.h>
#include <QFileDialog>
#include <Core/databasemanager.h>
#include <Core/applicationmanager.h>
#include <View/viewlistetrottinette.h>
#include <QDoubleValidator>

// Constructeur
ViewOffreLocation::ViewOffreLocation(const QString& ref_trotti, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewOffreLocation),
    m_RefTrotti(ref_trotti)
{
    ui->setupUi(this);
    // set text to auto return to line
    ui->warning->setWordWrap(true);

    // set data fields to accept only dates of the format dd/mm/yyyy hh:mm:ss
    ui->date_retour->setInputMask("99/99/9999 99:99:99");
    ui->date_retrait->setInputMask("99/99/9999 99:99:99");
    // set prix to only accept floats
    ui->prix_caution->setValidator( new QDoubleValidator(1, 4, 2, this) );
}

bool ViewOffreLocation::VerifyData()
{
    if (ApplicationManager::GetInstance().GetCurrentUser() == NULL){
        ui->warning->setText("ERROR : Cette fonction n'est pas disponible lorsque vous n'êtes pas connecté.");
        return false;
    }
    // check the reference and thats there is no offers in the db already associated with this
    QSqlQuery& res = DatabaseManager::GetInstance().Exec("SELECT * FROM locations WHERE ref_trotti = %s", m_RefTrotti.toLocal8Bit().constData());

    if (res.next()){ // Il ya des resultats alors return false et print l'error
        ui->warning->setText("Informations Incorrectes : La référence de la trottinette existe déjà dans la base de données.");
        return false;
    }

    // get both dates entered by the user
    QDateTime date_debut = QDateTime::fromString(ui->date_retrait->text(), "dd/MM/yyyy HH:mm:ss");
    QDateTime date_fin = QDateTime::fromString(ui->date_retour->text(), "dd/MM/yyyy HH:mm:ss");
    QDateTime right_now = QDateTime::fromString(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"), "dd/MM/yyyy HH:mm:ss");

    // check if the dates are valid ?
    if (date_fin < right_now || date_debut < right_now){
        ui->warning->setText("Informations Incorrectes : La date et l'heure actuelles doivent être antérieures à la date de fin et à la date de debut.");
        return false;
    }

    if (date_debut > date_fin){
        ui->warning->setText("Informations Incorrectes : La date de début doit être antérieure à la date de fin.");
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

    // Conversion de la date en ISO-8601 accepter par la bd
    date_debut = QDateTime::fromString(date_debut, "dd/MM/yyyy HH:mm:ss").toString("yyyy-MM-dd HH:mm:ss");
    date_fin = QDateTime::fromString(date_fin, "dd/MM/yyyy HH:mm:ss").toString("yyyy-MM-dd HH:mm:ss");

    // insert into the database
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
