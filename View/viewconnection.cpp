#include "viewconnection.h"
#include "ui_viewconnection.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <Core/databasemanager.h>
#include "mainwindow.h"

ViewConnection::ViewConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewConnection)
{
    ui->setupUi(this);
}

bool ViewConnection::VerifyLoginInformations()
{
    QString idf = ui->identifiant->text();
    QString mdp = ui->mdp->text();
    QSqlQuery r = DatabaseManager::GetInstance()
            .Exec("SELECT * FROM utilisateurs WHERE identifiant='%s';", idf.toLocal8Bit().constData());

    if (r.next()){
        QString mdp_hashed = QString(QCryptographicHash::hash(mdp.toLocal8Bit().constData(), QCryptographicHash::Sha256).toHex());

        if (mdp_hashed == r.value(4).toString()){
            return true;
        }else{
            ui->warning->setText("Mot de passe incorrect.");
            return false;
        }
    }else{
        ui->warning->setText("L'utilisateur que vous avez fourni n'existe pas.");
        return false;
    }

    return false;
}

void ViewConnection::FinishLogin()
{
    QString idf = ui->identifiant->text();

    QMessageBox::information(
        this,
        tr("Connection reussie"),
        QString("Bienvenue %1, vous êtes maintenant connecté.").arg(idf)
    );

    QDialog::accept();
    QLabel* user = ((MainWindow*)(this->parent()))->GetUI()->connected_user;
    user->setStyleSheet("color: green;");
    user->setText(QString("Connecté, utilisateur actuel: %1.").arg(idf));
}

void ViewConnection::accept()
{
    if (VerifyLoginInformations()){
        this->FinishLogin();
    }
}

ViewConnection::~ViewConnection()
{
    delete ui;
}
