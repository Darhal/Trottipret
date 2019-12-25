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
    ui->listTrotti->verticalHeader()->hide();
    ui->listTrotti->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->listTrotti->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->RefreshList();

    connect(ui->ajouterTrotti, &QPushButton::clicked, this, [this](){
        QDialog* dialog_wnd = new ViewAddTrottinette(this);;
        dialog_wnd->setAttribute(Qt::WA_DeleteOnClose); // Cela va liberer la memoire automatiquement
        dialog_wnd->show(); // Affiche notre boîte de dialogue
    });
    connect(ui->louer, &QPushButton::clicked, this, [this](){
        QModelIndex index = ui->listTrotti->currentIndex();
        QString ref = ui->listTrotti->item(index.row(), 0)->text();
        QDialog* dialog_wnd = new ViewOffreLocation(ref, this);;
        dialog_wnd->setAttribute(Qt::WA_DeleteOnClose); // Cela va liberer la memoire automatiquement
        dialog_wnd->show(); // Affiche notre boîte de dialogue
    });
    connect(ui->supprimer, &QPushButton::clicked, this, [this](){
        QModelIndex index = ui->listTrotti->currentIndex();
        QString status = ui->listTrotti->item(index.row(), 3)->text();
        QString ref = ui->listTrotti->item(index.row(), 0)->text();
        Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();

        if (cur_user && status != "EN LOCATION"){
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Etes-vous sur que vous voulez supprimer la trotinette par conséquence supprimer l'offre de location eventuel associer?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                DatabaseManager::GetInstance()
                        .Exec("DELETE FROM trottinettes WHERE ref_trotti='%s' AND identifiant='%s';",
                                ref.toLocal8Bit().constData(), cur_user->GetIdentifiant().toLocal8Bit().constData()
                             );
                DatabaseManager::GetInstance()
                        .Exec("DELETE FROM locations WHERE ref_trotti='%s' AND identifiant='%s';",
                                ref.toLocal8Bit().constData(), cur_user->GetIdentifiant().toLocal8Bit().constData()
                             );
                this->RefreshList();
            }
        }
    });
    connect(ui->listTrotti, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnRowSelection()));
    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    connect(ui->listTrotti, &QTableWidget::itemChanged, this,
        [this](QTableWidgetItem*item){
            QString ref = ui->listTrotti->item(item->row(), REF)->text();
            QString updated_text = item->text();

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
    connect(ui->fullView, &QPushButton::clicked, this, [this](){
        QModelIndex index = ui->listTrotti->currentIndex();
        int i = index.row();
        QString ref = ui->listTrotti->item(i, 0)->text();

        QSqlQuery& r = DatabaseManager::GetInstance()
                .Exec("SELECT image FROM trottinettes WHERE ref_trotti = '%s';", ref.toLocal8Bit().constData());

        if (r.first()){
            QByteArray image_bytes = r.value(0).toByteArray();
            QPixmap img_pixmap = QPixmap();
            img_pixmap.loadFromData( std::move(image_bytes) );

            QLabel* img = new QLabel(this); // creation d'une label
            img->setAttribute( Qt::WA_DeleteOnClose, true ); // pas besoin de free ca va free automatiquement on fermuture de la fenetre
            img->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            img->setWindowFlags(Qt::Window); // transformer en une fentre
            img->setPixmap(img_pixmap); // construire l'image
            img->show(); // affichage
        }
    });

    connect(ui->editPic, &QPushButton::clicked, this, [this](){
        QString m_ImageFilePath = QFileDialog::getOpenFileName(this, tr("Choose Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        QModelIndex index = ui->listTrotti->currentIndex();
        int i = index.row();
        QString ref = ui->listTrotti->item(i, 0)->text();
        QFile img(m_ImageFilePath);

        if (!img.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(
                this,
                tr("Error lors de l'ouverture de l'image"),
                QString("ERROR: Impossible d'ouvrir l'image que vous avez sélectionnée.")
            );
            return;
        }
        QByteArray buffer_byte_array = img.readAll();
        DatabaseManager::GetInstance().Prepare("UPDATE trottinettes SET image = :imageData WHERE ref_trotti = '%s';",
            ref.toLocal8Bit().constData()
        );
        DatabaseManager::GetInstance().BindValue(":imageData", buffer_byte_array);
        DatabaseManager::GetInstance().Exec();
        ui->imageTrotti->setPixmap(QPixmap(m_ImageFilePath));

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
    QModelIndex index = ui->listTrotti->currentIndex();
    int i = index.row();
    QString ref = ui->listTrotti->item(i, 0)->text();
    QString status = ui->listTrotti->item(i, 3)->text();

    if (status == QString("LIBRE")){
        ui->louer->setDisabled(false);
        ui->supprimer->setDisabled(false);
    }else{
        if (status == "EN LOCATION"){
            ui->supprimer->setDisabled(true);
        }else{
            ui->supprimer->setDisabled(false);
        }

        ui->louer->setDisabled(true);
    }

    QSqlQuery& r = DatabaseManager::GetInstance()
            .Exec("SELECT image FROM trottinettes WHERE ref_trotti = '%s';", ref.toLocal8Bit().constData());

    if (r.first()){
        QByteArray image_bytes = r.value(0).toByteArray();
        QPixmap img_pixmap = QPixmap();
        img_pixmap.loadFromData( std::move(image_bytes) );
        ui->imageTrotti->setPixmap(img_pixmap);
    }
}

void ViewListeTrottinette::RefreshList()
{
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();
    ui->listTrotti->setRowCount(0);;

    if (cur_user != NULL){
        QSqlQuery r(std::move(DatabaseManager::GetInstance()
                .Exec("SELECT * FROM trottinettes WHERE identifiant='%s';", cur_user->GetIdentifiant().toLocal8Bit().constData())));

        while (r.next()) {
            int row_count = ui->listTrotti->rowCount();
            ui->listTrotti->insertRow(row_count);

            for(int i = 0; i < 3; i++){
                QTableWidgetItem* item = new QTableWidgetItem(r.value(i).toString());
                ui->listTrotti->setItem(row_count, i, item);

                if (i == 0){
                    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                }
            }

            QSqlQuery& r2 = DatabaseManager::GetInstance()
                    .Exec("SELECT locataire FROM locations WHERE identifiant='%s' AND ref_trotti='%s';",
                          cur_user->GetIdentifiant().toLocal8Bit().constData(), r.value(0).toString().toLocal8Bit().constData());
           QTableWidgetItem* status = new QTableWidgetItem();
            if (r2.next()){
                QString loctaire = r2.value(0).toString();
                if (loctaire == ""){
                    status->setText("EN OFFRE");
                }else{
                    status->setText("EN LOCATION: "+loctaire);
                }
            }else{
                status->setText("LIBRE");
            }

            ui->listTrotti->setItem(row_count, 3, status);
        }
    }

    ui->supprimer->setDisabled(true);
    ui->louer->setDisabled(true);
}

ViewListeTrottinette::~ViewListeTrottinette()
{
    delete ui;
}
