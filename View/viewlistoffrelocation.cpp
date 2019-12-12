#include "viewlistoffrelocation.h"
#include "ui_viewlistoffrelocation.h"
#include "Core/applicationmanager.h"
#include "Core/databasemanager.h"
#include <qdebug.h>

ViewListOffreLocation::ViewListOffreLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewListOffreLocation)
{
    ui->setupUi(this);
    ui->tableOffLoc->verticalHeader()->hide();
    ui->tableOffLoc->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->tableOffLoc->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();

    if (cur_user != NULL){
        QSqlQuery& r = DatabaseManager::GetInstance()
                .Exec("SELECT * FROM offrelocations WHERE identifiant='%s';", cur_user->GetIdentifiant().toLocal8Bit().constData());
        while (r.next()){
            int row_count = ui->tableOffLoc->rowCount();
            ui->tableOffLoc->insertRow(row_count);

            for(int i = 1; i < 7; i++){
                ui->tableOffLoc->setItem(row_count, i - 1, new QTableWidgetItem(r.value(i).toString()));
            }
        }
    }

    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    connect(ui->tableOffLoc, &QTableWidget::itemChanged, this,
        [this](QTableWidgetItem*item){
            qDebug() << "Item changed (C:" << item->column() << "L:" << item->row();
        }
    );
}

ViewListOffreLocation::~ViewListOffreLocation()
{
    delete ui;
}
