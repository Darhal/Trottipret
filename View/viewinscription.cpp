#include "viewinscription.h"
#include "ui_viewinscription.h"
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>
#include <Core/databasemanager.h>


ViewInscription::ViewInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewInscription)
{
    ui->setupUi(this);
}

bool ViewInscription::VerifySignupInformations()
{
    QString email = ui->adrmail->text();
    QString idf = ui->identifiant->text();
    QString mdp = ui->mdp->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();

    if (!idf.isEmpty() && !email.isEmpty() && !mdp.isEmpty()){
        QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);
        if (!mailREX.exactMatch(email)){
            ui->warning->setText("INFORMATIONS INVALIDES: Veuillez verifier\nque l'adresse mail est correcte.");
            return false;
        }
        QSqlQuery r = DatabaseManager::GetInstance()
                .Exec("SELECT * FROM utilisateurs WHERE identifiant='%s';", idf.toLocal8Bit().constData());
        if (r.next()){
            ui->warning->setText("IDENTIFIANT DEJA UTILISE: Veuillez en choisir\nun autre.");
            return false;
        }
        return true;
    }else{
        ui->warning->setText("INFORMATIONS MANQUANTES: Veuillez renseigner\nl'identifiant,  l'adresse mail et le mot de pass.");
        return false;
    }
}

ViewInscription::~ViewInscription()
{
    delete ui;
}

void ViewInscription::on_buttonBox_accepted()
{}

void ViewInscription::FinishSignup()
{
    // At this stage all the informations all correct!
    QString email = ui->adrmail->text();
    QString idf = ui->identifiant->text();
    QString mdp = ui->mdp->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString mdp_hashed = QString(QCryptographicHash::hash(mdp.toLocal8Bit().constData(), QCryptographicHash::Sha256).toHex());

    DatabaseManager::GetInstance().
        Exec(
                "INSERT INTO utilisateurs (identifiant, nom, prenom, email, motdepass)"
                "VALUES ('%s', '%s', '%s', '%s', '%s');",
                idf.toLocal8Bit().constData(),
                nom.toLocal8Bit().constData(),
                prenom.toLocal8Bit().constData(),
                email.toLocal8Bit().constData(),
                mdp_hashed.toLocal8Bit().constData()
        );
    QMessageBox::information(
        this,
        tr("Inscription reussie"),
        QString("Vous vous êtes inscrit avec votre identifiant : %1.\n"
           "Veuillez le mémoriser car vous ne pourrez plus le changer plus tard.").arg(idf)
    );

    QDialog::accept();
}

void ViewInscription::accept()
{
    if (VerifySignupInformations()){
        this->FinishSignup();
    }
}
