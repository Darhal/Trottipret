#include "viewlocations.h"
#include "ui_viewlocations.h"
#include <Core/databasemanager.h>
#include <Core/applicationmanager.h>

ViewLocations::ViewLocations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewLocations)
{
    ui->setupUi(this);
    ui->location_tab->verticalHeader()->hide();
    ui->location_tab->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->location_tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->RefreshList();

    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    connect(ui->retour, &QPushButton::clicked, this, [this](){
        QModelIndex index = ui->location_tab->currentIndex();
        int i = index.row();
        QString owner = ui->location_tab->item(i, 0)->text();
        QString ref = ui->location_tab->item(i, 1)->text();

        DatabaseManager::GetInstance().Exec("UPDATE locations SET locataire = NULL WHERE identifiant='%s' AND ref_trotti='%s';",
                              owner.toLocal8Bit().constData(), ref.toLocal8Bit().constData()
        );

        this->RefreshList();
    });
}

void ViewLocations::RefreshList()
{
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();
    ui->location_tab->setRowCount(0);

    if (cur_user != NULL){
        QSqlQuery r = std::move(DatabaseManager::GetInstance()
                .Exec("SELECT * FROM locations WHERE locataire = '%s';", cur_user->GetIdentifiant().toLocal8Bit().constData()));
        QDateTime right_now = QDateTime::fromString(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"), "yyyy-MM-dd HH:mm:ss");

        while (r.next()){
            int row_count = ui->location_tab->rowCount();
            ui->location_tab->insertRow(row_count);
            QDateTime finish = QDateTime::fromString(r.value(3).toString(), "yyyy-MM-dd HH:mm:ss");
            bool is_red = right_now > finish;

            for(int i = 0; i < 6; i++){
                QTableWidgetItem* item = new QTableWidgetItem(r.value(i).toString());
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                ui->location_tab->setItem(row_count, i, item);

                if (is_red){
                    item->setBackgroundColor(QColor (250,0,0));
                }
            }
        }
    }
}

ViewLocations::~ViewLocations()
{
    delete ui;
}
