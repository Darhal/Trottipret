#include "viewconnection.h"
#include "ui_viewconnection.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <Core/databasemanager.h>
#include "mainwindow.h"
#include "Core/utilisateur.h"
#include "Core/applicationmanager.h"

// Constructeur generé par Qt
ViewConnection::ViewConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewConnection)
{
    ui->setupUi(this);
}

Utilisateur* ViewConnection::VerifyLoginInformations()
{
    QString idf = ui->identifiant->text(); // recupere l'identifiant
    QString mdp = ui->mdp->text(); // recupere le mot de passe
    // Effectue une requête de base de données en utilisant l'identifiant fourni
    QSqlQuery r = DatabaseManager::GetInstance()
            .Exec("SELECT * FROM utilisateurs WHERE identifiant='%s';", idf.toLocal8Bit().constData());

    if (r.next()){ // S'il ya des resultats
        // Nous allons hacher le mot de passe donné par l'utilisateur à l'aide de l'algorithme sha256,
        // contrairement à md5 et à d'autres algorithmes hérités, qui n'ont pas de collision
        // connue jusqu'à aujourd'hui et qui sont difficiles à résoudre.
        QString mdp_hashed = QString(QCryptographicHash::hash(mdp.toLocal8Bit().constData(),
                                                              QCryptographicHash::Sha256).toHex());

        // Nous comparons directement le mot de passe haché donné avec celui de la base de données.
        // Nous ne stockons pas les mots de passes en texte brut dans notre base de données,
        // ce qui en fait une bonne mesure de sécurité, ce qui rendra plus difficile
        // la tâche des pirates informatiques
        if (mdp_hashed == r.value(4).toString()){
            Utilisateur* user = new Utilisateur(r.value(0).toString(), r.value(3).toString(), r.value(1).toString(), r.value(2).toString(), r.value(4).toString());
            this->FinishLogin(user);  // faire le login
            return user; // connexion réussie :)
        }else{
            // mot de passe incorrect :(
            ui->warning->setText("Mot de passe incorrect.");
            return NULL;
        }
    }else{ // sinon (il ya pas de resultat, affiche l'erreur et retourne false)
        ui->warning->setText("L'utilisateur que vous avez fourni n'existe pas.");
        return NULL;
    }

    return NULL;
}

void ViewConnection::FinishLogin(Utilisateur* user)
{
    // Cette fonction est appelée uniquement après avoir vérifié les informations de connexion,
    // donc pas besoin de revérifier
    QString idf = ui->identifiant->text(); // recupere l'identifiant

    // Affiche une petite fenêtre informant l'utilisateur qu'il s'est connecté avec succès
    QMessageBox::information(
        this,
        tr("Connection reussie"),
        QString("Bienvenue %1, vous êtes maintenant connecté.").arg(idf)
    );

    QDialog::accept(); // ferme la fenêtre de dialog
    // Recupere le label de main window et le change en vert avec l'identifant de l'utilistauer actuel
    QLabel* user_label = ((MainWindow*)(this->parent()))->GetUI()->connected_user;
    user_label->setStyleSheet("color: green;");
    user_label->setText(QString("Connecté, utilisateur actuel: %1.").arg(idf));

    ApplicationManager.GetInstance().SetCurrentUser(user);
}

void ViewConnection::accept()
{
    // si les donnees sont bonnes terminé le login
    VerifyLoginInformations();
}

ViewConnection::~ViewConnection()
{
    delete ui; // libere les elements de l'UI
}
