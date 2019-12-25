#include "viewlistetrottinette.h"
#include "ui_viewlistetrottinette.h"
#include <Core/databasemanager.h>
#include <Core/applicationmanager.h>
#include <qdebug.h>
#include <View/viewoffrelocation.h>
#include <View/viewaddtrottinette.h>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

ViewListeTrottinette::ViewListeTrottinette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewListeTrottinette)
{
    ui->setupUi(this);
    // Set items in the table to auto adapt
    ui->listTrotti->verticalHeader()->hide();
    ui->listTrotti->setSelectionBehavior((QAbstractItemView::SelectRows)); // select whole row
    ui->listTrotti->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->RefreshList();

    // Handle logic of adding new trottinete
    connect(ui->ajouterTrotti, &QPushButton::clicked, this, [this](){
        QDialog* dialog_wnd = new ViewAddTrottinette(this); // open the window responsible for that
        dialog_wnd->setAttribute(Qt::WA_DeleteOnClose); // Cela va liberer la memoire automatiquement
        dialog_wnd->show(); // Affiche notre boîte de dialogue
    });

    //Handle the logic for propsing a renting offer
    connect(ui->louer, &QPushButton::clicked, this, [this](){
        QModelIndex index = ui->listTrotti->currentIndex(); // get current selection index
        QString ref = ui->listTrotti->item(index.row(), 0)->text(); // get the trotti ref
        QDialog* dialog_wnd = new ViewOffreLocation(ref, this); // open the window with passing the ref
        dialog_wnd->setAttribute(Qt::WA_DeleteOnClose); // Cela va liberer la memoire automatiquement
        dialog_wnd->show(); // Affiche notre boîte de dialogue
    });

    // Handle the logic of deleteing a trotti from the lsit
    connect(ui->supprimer, &QPushButton::clicked, this, [this](){
        QModelIndex index = ui->listTrotti->currentIndex(); // get index
        QString status = ui->listTrotti->item(index.row(), 3)->text(); //get status (libre, en offre, en location)
        QString ref = ui->listTrotti->item(index.row(), 0)->text(); // get ref
        Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser(); // get current user

        if (cur_user && !status.contains("EN LOCATION")){ // check status if its not already in renting then
            // prompt a confimration
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Etes-vous sur que vous voulez supprimer la trotinette par conséquence supprimer l'offre de location eventuel associer?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) { // if yes clicked
                // delete trotti from our database
                DatabaseManager::GetInstance()
                        .Exec("DELETE FROM trottinettes WHERE ref_trotti='%s' AND identifiant='%s';",
                                ref.toLocal8Bit().constData(), cur_user->GetIdentifiant().toLocal8Bit().constData()
                             );
                // also clear all the offers associated with it
                DatabaseManager::GetInstance()
                        .Exec("DELETE FROM locations WHERE ref_trotti='%s' AND identifiant='%s';",
                                ref.toLocal8Bit().constData(), cur_user->GetIdentifiant().toLocal8Bit().constData()
                             );
                // refresh the table view
                this->RefreshList();
            }
        }
    });
    // handle the logic on selection new rows
    connect(ui->listTrotti, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnRowSelection()));
    // Close the window
    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    // Detect change on the items of the table
    connect(ui->listTrotti, &QTableWidget::itemChanged, this,
        [this](QTableWidgetItem*item){
            // get the row and the new text
            QString ref = ui->listTrotti->item(item->row(), REF)->text();
            QString updated_text = item->text();

            // update the databse accordingaly (based on colum id)
            switch((Cols)item->column()){
            case REF:
                break;
            case MODEL:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE trottinettes SET model = '%s' WHERE ref_trotti='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData()
                             );
                break;
            case ETAT:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE trottinettes SET etat = '%s' WHERE ref_trotti='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData()
                              );
                break;
            default:
                break;
            };
        }
    );

    // See a full view of the picture in its real size
    connect(ui->fullView, &QPushButton::clicked, this, [this](){
        // get current index and referncce
        QModelIndex index = ui->listTrotti->currentIndex();
        int i = index.row();
        QString ref = ui->listTrotti->item(i, 0)->text();

        // get the image
        QSqlQuery& r = DatabaseManager::GetInstance()
                .Exec("SELECT image FROM trottinettes WHERE ref_trotti = '%s';", ref.toLocal8Bit().constData());

        if (r.first() && r.value(0).toString() != ""){ // if there is results valid ones
            QByteArray image_bytes = r.value(0).toByteArray(); // get the byte array
            QPixmap img_pixmap = QPixmap(); // construct a pixmap (image)
            img_pixmap.loadFromData( std::move(image_bytes) ); // based on the byte array

            QLabel* img = new QLabel(this); // creation d'une label
            img->setAttribute( Qt::WA_DeleteOnClose, true ); // pas besoin de free ca va free automatiquement on fermuture de la fenetre
            img->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            img->setWindowFlags(Qt::Window); // transformer en une fentre
            img->setPixmap(img_pixmap); // construire l'image
            img->show(); // affichage
        }
    });

    // Handle the logic of changing the trotti picturte
    connect(ui->editPic, &QPushButton::clicked, this, [this](){
        // open dialog for selction of the files
        QString m_ImageFilePath = QFileDialog::getOpenFileName(this, tr("Choose Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        // get the refernce
        QModelIndex index = ui->listTrotti->currentIndex();
        int i = index.row();
        QString ref = ui->listTrotti->item(i, 0)->text();
        // open a file
        QFile img(m_ImageFilePath);

        if (!img.open(QIODevice::ReadOnly)) { // handle errors
            QMessageBox::critical(
                this,
                tr("Error lors de l'ouverture de l'image"),
                QString("ERROR: Impossible d'ouvrir l'image que vous avez sélectionnée.")
            );
            return;
        }
        // read all bytes
        QByteArray buffer_byte_array = img.readAll();
        // prepare for db querry
        DatabaseManager::GetInstance().Prepare("UPDATE trottinettes SET image = :imageData WHERE ref_trotti = '%s';",
            ref.toLocal8Bit().constData()
        );
        // bind the balue
        DatabaseManager::GetInstance().BindValue(":imageData", buffer_byte_array);
        // run
        DatabaseManager::GetInstance().Exec();
        ui->imageTrotti->setPixmap(QPixmap(m_ImageFilePath)); // update the label image

        // Petite fenêtre pour informer l'utilisateur que tout va bien
        QMessageBox::information(
            this,
            tr("Modification De L'Image Trottinette"),
            QString("L'image a été mise à jour avec succès.")
        );
    });
}

void ViewListeTrottinette::OnRowSelection()
{
    // get current index, refernce and status
    QModelIndex index = ui->listTrotti->currentIndex();
    int i = index.row();
    QString ref = ui->listTrotti->item(i, 0)->text();
    QString status = ui->listTrotti->item(i, 3)->text();

    // Handle the logic for diasble / enable the buttons responsible for renting and deleting
    if (status == QString("LIBRE")){ // si libre
        ui->louer->setDisabled(false); // on peut louer
        ui->supprimer->setDisabled(false); // on peut supprimer
    }else{
        if (status.contains("EN LOCATION")){ // si on location
            ui->supprimer->setDisabled(true); // disable suppression
        }else{
            ui->supprimer->setDisabled(false); // sinon enable it
        }

        ui->louer->setDisabled(true); // disable renting we cant rent twice the same trotti
    }

    // get image from fb
    QSqlQuery& r = DatabaseManager::GetInstance()
            .Exec("SELECT image FROM trottinettes WHERE ref_trotti = '%s';", ref.toLocal8Bit().constData());

    if (r.first() && r.value(0).toString() != ""){ // if there is image
        // reconstruct it back based on the raw data (binaries)
        QByteArray image_bytes = r.value(0).toByteArray();
        QPixmap img_pixmap = QPixmap();
        img_pixmap.loadFromData( std::move(image_bytes) );
        ui->imageTrotti->setPixmap(img_pixmap);
        // set it to fit the label
        ui->imageTrotti->setScaledContents( true );
        ui->imageTrotti->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }else{ // there is no image here so show the default one
        QPixmap img_pixmap = QPixmap(":/Resources/Images/trotinette.png");
        ui->imageTrotti->setPixmap(img_pixmap);
        ui->imageTrotti->setScaledContents( true );
        ui->imageTrotti->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void ViewListeTrottinette::RefreshList()
{
    // get current user
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();
    ui->listTrotti->setRowCount(0); // delete everything

    if (cur_user != NULL){
        // get list of trottis
        QSqlQuery r(std::move(DatabaseManager::GetInstance()
                .Exec("SELECT * FROM trottinettes WHERE identifiant='%s';", cur_user->GetIdentifiant().toLocal8Bit().constData())));

        while (r.next()) { // tant que il ya des resultats faire
            int row_count = ui->listTrotti->rowCount();
            ui->listTrotti->insertRow(row_count); // insert new row

            for(int i = 0; i < 3; i++){
                // added the items
                QTableWidgetItem* item = new QTableWidgetItem(r.value(i).toString());
                ui->listTrotti->setItem(row_count, i, item);

                if (i == 0){
                    item->setFlags(item->flags() ^ Qt::ItemIsEditable); // set the refernce to inmutable (cant be edited)
                }
            }

            // perofmr a joint (jointure) to check the status of the trotti (en location or not)
            QSqlQuery& r2 = DatabaseManager::GetInstance()
                    .Exec("SELECT locataire FROM locations WHERE identifiant='%s' AND ref_trotti='%s';",
                          cur_user->GetIdentifiant().toLocal8Bit().constData(), r.value(0).toString().toLocal8Bit().constData());
           QTableWidgetItem* status = new QTableWidgetItem();
            if (r2.next()){ // if there results
                QString loctaire = r2.value(0).toString();
                if (loctaire == ""){ // if the locataire is empty then its en offre
                    status->setText("EN OFFRE");
                }else{
                    status->setText("EN LOCATION: "+loctaire); // otherwise there is someone renting it
                }
            }else{
                status->setText("LIBRE"); // otherwise its free
            }

            ui->listTrotti->setItem(row_count, 3, status);
        }
    }

    // disable everything
    ui->supprimer->setDisabled(true);
    ui->louer->setDisabled(true);
}

ViewListeTrottinette::~ViewListeTrottinette()
{
    delete ui;
}
