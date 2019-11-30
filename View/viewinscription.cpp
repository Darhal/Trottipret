#include "viewinscription.h"
#include "ui_viewinscription.h"
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>
#include <Core/databasemanager.h>

// Ctor fourni par Qt
ViewInscription::ViewInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewInscription)
{
    ui->setupUi(this);
}

bool ViewInscription::VerifySignupInformations()
{
    // Recupere les donnees
    QString email = ui->adrmail->text();
    QString idf = ui->identifiant->text();
    QString mdp = ui->mdp->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();

    // Si l'email, l'identifiant et la mdp ne sont pas vides alors
    if (!idf.isEmpty() && !email.isEmpty() && !mdp.isEmpty()){
        // Un regex qui va verfier que il s'agit bien d'un email et pas autre
        QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);
        if (!mailREX.exactMatch(email)){ // Si ca ne correspond pas au regex alors retourne faux et afficher error
            ui->warning->setText("INFORMATIONS INVALIDES: Veuillez verifier\nque l'adresse mail est correcte.");
            return false;
        }

        // Effectuer une requête sur la base de données avec le nom d'utilisateur donné pour
        // vérifier si l'utilisateur existe déjà
        QSqlQuery r = DatabaseManager::GetInstance()
                .Exec("SELECT * FROM utilisateurs WHERE identifiant='%s';", idf.toLocal8Bit().constData());
        if (r.next()){ // Il ya des resultats alors retourne false et print l'error
            ui->warning->setText("IDENTIFIANT DEJA UTILISE: Veuillez en choisir\nun autre.");
            return false;
        }

        return true; // toute est bon on peut faire le signup
    }else{ // l'und es champs sont vides!
        ui->warning->setText("INFORMATIONS MANQUANTES: Veuillez renseigner\nl'identifiant,  l'adresse mail et le mot de pass.");
        return false;
    }
}

ViewInscription::~ViewInscription()
{
    delete ui; // libere le UI
}

void ViewInscription::on_buttonBox_accepted()
{}

void ViewInscription::FinishSignup()
{
    // A cette ettape toutes les informations sont correctes!

    // Recupere les informations
    QString email = ui->adrmail->text();
    QString idf = ui->identifiant->text();
    QString mdp = ui->mdp->text();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();

    // Très bien, nous allons maintenant hacher le mot de passe, car il est dangereux et peu pratique de
    // stocker le mot de passe sous forme de texte brut dans la base de données car il peut être
    // facilement piraté. et plus tard, pour vérifier si le login est correct, nous hachons ce que
    // l'utilisateur a fourni et le comparons déjà au hachage de la base de données
    QString mdp_hashed = QString(QCryptographicHash::hash(mdp.toLocal8Bit().constData(), QCryptographicHash::Sha256).toHex());

    // Appelez notre gestionnaire de base de données et effectuez
    // une requête pour insérer le nouvel utilisateur.
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

    // Petite fenêtre pour informer l'utilisateur que tout va bien et
    // qu'il s'est enregistré avec succès
    QMessageBox::information(
        this,
        tr("Inscription reussie"),
        QString("Vous vous êtes inscrit avec votre identifiant : %1.\n"
           "Veuillez le mémoriser car vous ne pourrez plus le changer plus tard.").arg(idf)
    );

    QDialog::accept(); // fermer la fentre de dialog
}

void ViewInscription::accept()
{
    // L'événement viendra ici en premier
    if (VerifySignupInformations()){ // verification des donnes: email, utilisateur qui existe deja etc...
        this->FinishSignup(); // faire le signup
    }
}
