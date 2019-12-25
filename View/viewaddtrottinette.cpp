#include "viewaddtrottinette.h"
#include "ui_viewaddtrottinette.h"
#include "Core/databasemanager.h"
#include "Core/utilisateur.h"
#include <QFileDialog>
#include "Core/applicationmanager.h"
#include <QDebug>
#include <QMessageBox>
#include "View/viewlistetrottinette.h"

ViewAddTrottinette::ViewAddTrottinette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAddTrottinette)
{
    ui->setupUi(this);
    ui->img_label->setWordWrap(true); // The text will automatically return to line

    // Handle the selection of the photo for the trotti
    connect(ui->choisirPhoto, &QPushButton::clicked, [this](){
        m_ImageFilePath = QFileDialog::getOpenFileName(this,
               tr("Choose Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        ui->img_label->setText("Image: "+m_ImageFilePath); // update label
    });

    // Show the picture selected by the user when its clicked
    connect(ui->voirPhoto, &QPushButton::clicked, this, [this](){
        if (m_ImageFilePath != ""){ // if path is not empty then
            QLabel* img = new QLabel(this); // creation d'une label
            img->setAttribute( Qt::WA_DeleteOnClose, true ); // pas besoin de free ca va free automatiquement on fermuture de la fenetre
            img->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            img->setWindowFlags(Qt::Window); // transformer en une fentre
            img->setPixmap(QPixmap(m_ImageFilePath, 0, Qt::AutoColor)); // construire l'image
            img->show(); // affichage
        }
    });
}

bool ViewAddTrottinette::VerifyData()
{
    // if there is current user
    if (ApplicationManager::GetInstance().GetCurrentUser() == NULL){
        ui->warning->setText("ERROR: Cette fonction n'est pas disponible lorsque vous n'êtes pas connecté.");
        return false;
    }

    QString ref = ui->ref->text(); // get reference
    QSqlQuery& res = DatabaseManager::GetInstance().Exec("SELECT * FROM trottinettes WHERE ref_trotti = '%s'", ref.toLocal8Bit().constData());

    // verify that there is no dup)licate oif reference
    if (res.next()){ // Il ya des resultats alors return false et print l'error
        ui->warning->setText("ERROR: La référence de la trottinette existe déjà dans la base de données.");
        return false;
    }

    return true;
}

void ViewAddTrottinette::SubmitData()
{
    QString ref = ui->ref->text();
    QString model = ui->model->text();
    QString etat = ui->etat->currentText();

    if (!m_ImageFilePath.isEmpty() && m_ImageFilePath != ""){ // if the user selected an image
        QFile img(m_ImageFilePath); // read the file

        if (!img.open(QIODevice::ReadOnly)) { // handle errors
            ui->warning->setText("ERROR: Impossible d'ouvrir l'image que vous avez sélectionnée.");
            return;
        }
        QByteArray buffer_byte_array = img.readAll(); // read the bytes
        // there is an alternative to this which is the code below
        /*QImage trotti_pic;
        trotti_pic.load(m_ImageFilePath);
        QByteArray buffer_byte_array = QByteArray::fromRawData((const char*)trotti_pic.bits(), trotti_pic.byteCount());*/

        // Prepare for a sql querry
        DatabaseManager::GetInstance().
            Prepare(
                    "INSERT INTO trottinettes (ref_trotti, model, etat, image, identifiant)"
                    "VALUES ('%s', '%s', '%s', :imageData, '%s');",
                    ref.toLocal8Bit().constData(),
                    model.toLocal8Bit().constData(),
                    etat.toLocal8Bit().constData(),
                    ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant().toLocal8Bit().constData()
            );
        // bind the value ':imageData' to the binary data of the image
        DatabaseManager::GetInstance().BindValue(":imageData", buffer_byte_array);
        DatabaseManager::GetInstance().Exec(); // finally execute the sql command
    }else{
        // there is no image here so we run the command straight away
        DatabaseManager::GetInstance().
            Exec(
                    "INSERT INTO trottinettes (ref_trotti, model, etat, image, identifiant)"
                    "VALUES ('%s', '%s', '%s', NULL, '%s');",
                    ref.toLocal8Bit().constData(),
                    model.toLocal8Bit().constData(),
                    etat.toLocal8Bit().constData(),
                    ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant().toLocal8Bit().constData()
            );
    }

    // Petite fenêtre pour informer l'utilisateur que tout va bien
    QMessageBox::information(
        this,
        tr("Ajouter Une Trottinette"),
        QString("Votre trotinette a été bien ajouté dans notre base de donées.")
    );

    // Update the list of trottinete owned by the user
    ((ViewListeTrottinette*)parent())->RefreshList();
    QDialog::accept(); // fermer la fenêtre de dialog
}


void ViewAddTrottinette::accept()
{
    if (this->VerifyData()){ // verify data
        this->SubmitData(); // submit if verified
    }
}

ViewAddTrottinette::~ViewAddTrottinette()
{
    delete ui; // free data
}
