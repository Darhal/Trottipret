#include "viewoffrelocation.h"
#include "ui_viewoffrelocation.h"
#include <QMessageBox>
#include <Core/databasemanager.h>
#include <Core/applicationmanager.h>
#include <qdebug.h>
#include <QFileDialog>

// Constructeur
ViewOffreLocation::ViewOffreLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewOffreLocation)
{
    ui->setupUi(this);

    connect(ui->choisirPhoto, &QPushButton::clicked, [this](){
        m_ImageFilePath = QFileDialog::getOpenFileName(this,
               tr("Choose Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    });
}

bool ViewOffreLocation::VerifyData()
{
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

    if (!m_ImageFilePath.isEmpty() && m_ImageFilePath != ""){
        QFile img(m_ImageFilePath);

        if (!img.open(QIODevice::ReadOnly)) {
            qDebug() << "Cant open file!";
            return;
        }
        QByteArray buffer_byte_array = img.readAll();
        /*QImage trotti_pic;
        trotti_pic.load(m_ImageFilePath);
        QByteArray buffer_byte_array = QByteArray::fromRawData((const char*)trotti_pic.bits(), trotti_pic.byteCount());*/

        DatabaseManager::GetInstance().
            Prepare(
                    "INSERT INTO trottinettes (ref_trotti, model, etat, image, identifiant)"
                    "VALUES ('%s', '%s', '%s', :imageData, '%s');",
                    ref.toLocal8Bit().constData(),
                    model.toLocal8Bit().constData(),
                    etat.toLocal8Bit().constData(),
                    ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant().toLocal8Bit().constData()
            );
        DatabaseManager::GetInstance().BindValue(":imageData", buffer_byte_array);
        DatabaseManager::GetInstance().Exec();
    }else{
        DatabaseManager::GetInstance().
            Exec(
                    "INSERT INTO trottinettes (ref_trotti, model, etat, image, identifiant)"
                    "VALUES ('%s', '%s', '%s', 'NULL', '%s');",
                    ref.toLocal8Bit().constData(),
                    model.toLocal8Bit().constData(),
                    etat.toLocal8Bit().constData(),
                    ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant().toLocal8Bit().constData()
            );
    }

    DatabaseManager::GetInstance().
        Exec(
                "INSERT INTO offrelocations (identifiant, ref_trotti, date_debut, date_fin, lieu_debut, lieu_fin, prix_caution)"
                "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%f');",
                ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant().toLocal8Bit().constData(),
                ref.toLocal8Bit().constData(),
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
