#include "viewinscription.h"
#include "ui_viewinscription.h"
#include <QCryptographicHash>
#include <QDebug>

ViewInscription::ViewInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewInscription)
{
    ui->setupUi(this);
}

bool ViewInscription::VerifySignupInformations()
{
    qInfo() << "Login started!";

    QString email = ui->adrmail->text();
    QString idf = ui->identifiant->text();
    QString mdp = ui->mdp->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();

    if (!idf.isEmpty() && !email.isEmpty() && !mdp.isEmpty()){
        return true;
    }else{
        ui->warning->setText("Informations manquantes, veuillez renseigner\nl'identifiant,  l'adresse mail et le mot de pass.");
        return false;
    }
}

ViewInscription::~ViewInscription()
{
    delete ui;
}

void ViewInscription::on_buttonBox_accepted()
{
    qDebug() << "Signup scuessful!";
}

void ViewInscription::accept()
{
    if (VerifySignupInformations()){
        QDialog::accept();
    }else{
        return;
    }
}
