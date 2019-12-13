#include "viewalloffre.h"
#include "ui_viewalloffre.h"
#include "Core/databasemanager.h"
#include "Core/utilisateur.h"
#include "Core/applicationmanager.h"

ViewAllOffre::ViewAllOffre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAllOffre)
{
    ui->setupUi(this);
    ui->all_offers->verticalHeader()->hide();
    ui->all_offers->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->all_offers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();
    QSqlQuery* r = NULL;
    if (cur_user != NULL){
        r = &DatabaseManager::GetInstance().Exec("SELECT * FROM offrelocations WHERE identifiant !=' %s';",
                                                     cur_user->GetIdentifiant().toLocal8Bit().constData());
    }else{
        r = &DatabaseManager::GetInstance().Exec("SELECT * FROM offrelocations;");
    }

    while (r && r->next()){
        int row_count = ui->all_offers->rowCount();
        ui->all_offers->insertRow(row_count);

        for(int i = 0; i < 7; i++){
            QTableWidgetItem* item = new QTableWidgetItem(r->value(i).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->all_offers->setItem(row_count, i, item);
        }
    }

    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
}

ViewAllOffre::~ViewAllOffre()
{
    delete ui;
}
