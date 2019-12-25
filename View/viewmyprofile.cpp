#include "viewmyprofile.h"
#include "ui_viewmyprofile.h"
#include <Core/applicationmanager.h>
#include <Core/utilisateur.h>
#include <Core/databasemanager.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QBitmap>
#include <QPixmap>
#include <QPainter>
#include <QCryptographicHash>

ViewMyProfile::ViewMyProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewMyProfile)
{
    ui->setupUi(this);
    // Set text to auto return to line
    ui->warning->setWordWrap(true);
    ui->tip->setWordWrap(true);
    // align center
    ui->idf->setAlignment(Qt::AlignCenter);
    Utilisateur* cur_usr = ApplicationManager::GetInstance().GetCurrentUser(); // get current user

    if (cur_usr != nullptr){ // if user isnt not null (annoynme)
        // set all the edit fields to the data of the user
        ui->adrmail->setText(cur_usr->GetAdresseMail());
        ui->nom->setText(cur_usr->GetNom());
        ui->mdp->setText(cur_usr->GetMdp());
        ui->prenom->setText(cur_usr->GetPrenom());
        ui->idf->setText("Identifiant: "+cur_usr->GetIdentifiant());

        // get avatar from db
        QSqlQuery& r = DatabaseManager::GetInstance()
                .Exec("SELECT avatar FROM utilisateurs WHERE identifiant = '%s';", cur_usr->GetIdentifiant().toLocal8Bit().constData());

        if (r.first() && r.value(0).toString() != ""){ // If there is image
            QByteArray image_bytes = r.value(0).toByteArray();
            QPixmap img_pixmap = QPixmap();
            img_pixmap.loadFromData( std::move(image_bytes) );
            this->SetAvatarPicture(img_pixmap);
        }else{ // if its not
            // display the default avatar
            QPixmap img_pixmap = QPixmap(":/Resources/Images/user.png");
            this->SetAvatarPicture(img_pixmap);
        }
    }

    // Handle the change in the avatar
    connect(ui->changeAvatar, &QPushButton::clicked, this, [this](){
        m_AvatarPath = QFileDialog::getOpenFileName(this,
               tr("Choose Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        QPixmap avatar = QPixmap(m_AvatarPath);
        this->SetAvatarPicture(avatar);
    });
}

void ViewMyProfile::SetAvatarPicture(QPixmap& img)
{
    // Draw the mask.
    /*QBitmap  mask(img.size());
    QPainter painter(&mask);
    mask.fill(Qt::white);
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(mask.width()/2, mask.height()/2), 100, 100);

    // Draw the final image.
    img.setMask(mask);*/

    // display the image
    ui->avatar->setPixmap(img);
    ui->avatar->setScaledContents( true );
    ui->avatar->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

bool ViewMyProfile::VerifyInfo()
{
    QString email = ui->adrmail->text();

    if (!email.isEmpty() ){ // if the email isnt empty then we havbe to verify its correct
        // Un regex qui va verifier qu'il s'agit bien d'un email et pas autre
        QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);
        if (!mailREX.exactMatch(email)){ // Si ça ne correspond pas au regex alors retourne faux et affiche error
            ui->warning->setText("INFORMATIONS INVALIDES: Veuillez verifier que l'adresse mail est correcte.");
            return false;
        }
    }

    return true;
}

void ViewMyProfile::FinishEdit()
{
     Utilisateur* cur_usr = ApplicationManager::GetInstance().GetCurrentUser();
     if (!cur_usr) return; // if there is no current user then abort
     QString idf = cur_usr->GetIdentifiant(); // get the current idrentifiant

     if (m_AvatarPath != ""){ // if the avatar path isnt empty then
        QFile img(m_AvatarPath); // laod the file

        if (!img.open(QIODevice::ReadOnly)) { // handle errors
            QMessageBox::critical(
                this,
                tr("Error lors de l'ouverture de l'image"),
                QString("ERROR: Impossible d'ouvrir l'image que vous avez sélectionnée comme avatar.")
            );
            return;
        }

        // read bytes
        QByteArray buffer_byte_array = img.readAll();
        //prepare the db querry
        DatabaseManager::GetInstance().Prepare("UPDATE utilisateurs SET avatar = :imageData WHERE identifiant = '%s';",
            idf.toLocal8Bit().constData()
        );
        // bind the binary data
        DatabaseManager::GetInstance().BindValue(":imageData", buffer_byte_array);
        DatabaseManager::GetInstance().Exec(); // run
    }

    // Handle the logic of change in password
    QSqlQuery& r = DatabaseManager::GetInstance()
            .Exec("SELECT motdepass FROM utilisateurs WHERE identifiant='%s';", idf.toLocal8Bit().constData());

    if (r.next()){ // S'il ya des resultats
        if (ui->mdp->text() != r.value(0).toString()){ // if its not the same hash then the user must have changed smthg
            // get the new passowrd and hash it and update the db
            QString mdp_hashed = QString(QCryptographicHash::hash(ui->mdp->text().toLocal8Bit().constData(), QCryptographicHash::Sha256).toHex());
            cur_usr->SetMdp(mdp_hashed);
            DatabaseManager::GetInstance()
                    .Exec("UPDATE utilisateurs SET motdepass = '%s' WHERE identifiant='%s';",
                            mdp_hashed.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                         );
        }
    }

    // update everything else email, nom and prenom
    DatabaseManager::GetInstance()
            .Exec("UPDATE utilisateurs SET nom='%s', prenom='%s', email='%s' WHERE identifiant='%s';",
                    ui->nom->text().toLocal8Bit().constData(), ui->prenom->text().toLocal8Bit().constData(),
                    ui->adrmail->text().toLocal8Bit().constData(),
                    idf.toLocal8Bit().constData()
                 );

    // update the edit boxes
    cur_usr->SetAdresseMail(ui->adrmail->text());
    cur_usr->SetNom(ui->nom->text());
    cur_usr->SetPrenom(ui->prenom->text());

    // Petite fenêtre pour informer l'utilisateur que tout va bien et
    // qu'il s'est enregistré avec succès
    QMessageBox::information(
        this,
        tr("Modification Reussie"),
        QString("Toutes les modifications ont été enregistrées avec succès.")
    );

    QDialog::accept(); // fermer la fenêtre de dialog
}

void ViewMyProfile::accept()
{
    if (VerifyInfo()){ // verification des donnees: email, utilisateur qui existe deja etc...
        this->FinishEdit(); // faire le signup
    }
}

ViewMyProfile::~ViewMyProfile()
{
    delete ui;
}
