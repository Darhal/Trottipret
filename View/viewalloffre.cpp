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
    ui->all_offers->verticalHeader()->hide();
    ui->all_offers->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->all_offers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->RefreshList();

    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    connect(ui->louer, &QPushButton::clicked, this, [this](){
        Utilisateur* user = ApplicationManager::GetInstance().GetCurrentUser();
        if (!user) return;
        QModelIndex index = ui->all_offers->currentIndex();
        QString owner = ui->all_offers->item(index.row(), 0)->text();
        QString ref = ui->all_offers->item(index.row(), 1)->text();

        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Etes-vous sur que vous voulez louer la trotinette?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            DatabaseManager::GetInstance().Exec("UPDATE locations SET locataire = '%s' WHERE identifiant='%s' AND ref_trotti='%s';",
                                  user->GetIdentifiant().toLocal8Bit().constData(), owner.toLocal8Bit().constData(), ref.toLocal8Bit().constData()
            );
            this->RefreshList();
        }
    });
}

void ViewAllOffre::RefreshList()
{
    ui->all_offers->setRowCount(0);
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();
    QSqlQuery r;
    if (cur_user != NULL){
        r = DatabaseManager::GetInstance().Exec("SELECT * FROM locations WHERE identifiant != '%s' AND locataire is NULL;",
                                                     cur_user->GetIdentifiant().toLocal8Bit().constData());
    }else{
        r = DatabaseManager::GetInstance().Exec("SELECT * FROM locations WHERE locataire is NULL;");
    }

    while (r.next()){
        int row_count = ui->all_offers->rowCount();
        ui->all_offers->insertRow(row_count);

        for(int i = 0; i < 7; i++){
            QTableWidgetItem* item = new QTableWidgetItem(r.value(i).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->all_offers->setItem(row_count, i, item);
        }
    }
}

ViewAllOffre::~ViewAllOffre()
{
    delete ui;
}
