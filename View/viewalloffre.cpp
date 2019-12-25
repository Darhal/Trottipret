#include "viewalloffre.h"
#include "ui_viewalloffre.h"
#include "Core/databasemanager.h"
#include "Core/utilisateur.h"
#include "Core/applicationmanager.h"
#include <QMessageBox>

ViewAllOffre::ViewAllOffre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAllOffre)
{
    ui->setupUi(this);
    // Set the QTableVIew to auto adapt the items inside it
    ui->all_offers->verticalHeader()->hide();
    ui->all_offers->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->all_offers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->RefreshList(); // refresh list this will update the table

    // close when click on frermer
    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});

    // Handle the logic of louer une trottinette
    connect(ui->louer, &QPushButton::clicked, this, [this](){
        Utilisateur* user = ApplicationManager::GetInstance().GetCurrentUser(); // get current user
        if (!user) return; // if there is nonne then abort
        // get selected offre
        QModelIndex index = ui->all_offers->currentIndex();
        QString owner = ui->all_offers->item(index.row(), 0)->text();
        QString ref = ui->all_offers->item(index.row(), 1)->text();

        // promot a confimration box
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Etes-vous sur que vous voulez louer la trotinette?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) { // if yes clicked then do the following
            // update the locataire to the current user
            DatabaseManager::GetInstance().Exec("UPDATE locations SET locataire = '%s' WHERE identifiant='%s' AND ref_trotti='%s';",
                                  user->GetIdentifiant().toLocal8Bit().constData(), owner.toLocal8Bit().constData(), ref.toLocal8Bit().constData()
            );
            // update the list (MCV model) this will remove the offer
            this->RefreshList();
        }
    });
}

void ViewAllOffre::RefreshList()
{
    ui->all_offers->setRowCount(0); // remove everything
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser(); // current user
    QSqlQuery r;
    if (cur_user != NULL){ //  if the user is not annonymous
        // get every offer not proposed by the current user
        r = DatabaseManager::GetInstance().Exec("SELECT * FROM locations WHERE identifiant != '%s' AND locataire is NULL;",
                                                     cur_user->GetIdentifiant().toLocal8Bit().constData());
    }else{
        // get all ofers we are annonymous (not login)
        r = DatabaseManager::GetInstance().Exec("SELECT * FROM locations WHERE locataire is NULL;");
    }

    while (r.next()){ // while there is results
        // Insert new row
        int row_count = ui->all_offers->rowCount();
        ui->all_offers->insertRow(row_count);

        // Set the items
        for(int i = 0; i < 7; i++){
            QTableWidgetItem* item = new QTableWidgetItem(r.value(i).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable); // No edits!
            ui->all_offers->setItem(row_count, i, item);
        }
    }
}

ViewAllOffre::~ViewAllOffre()
{
    delete ui;
}
