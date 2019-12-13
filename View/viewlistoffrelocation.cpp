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
                QTableWidgetItem* item = new QTableWidgetItem(r.value(i).toString());
                if (i == 1){
                    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                }
                ui->tableOffLoc->setItem(row_count, i - 1, item);
            }
        }
    }

    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    connect(ui->tableOffLoc, &QTableWidget::itemChanged, this,
        [this](QTableWidgetItem*item){
            QString ref = ui->tableOffLoc->itemAt(item->row(), REF)->text();
            QString updated_text = item->text();
            QString idf = ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant();

            switch((Cols)item->column()){
            case REF:
                break;
            case DATE_DEBUT:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE offrelocations SET date_debut = '%s' WHERE ref_trotti='%s' AND identifiant='%s' ;",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                             );
                break;
            case DATE_FIN:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE offrelocations SET date_fin = '%s' WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                              );
                break;
            case LIEU_DEBUT:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE offrelocations SET lieu_debut = '%s' WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                              );
                break;
            case LIEU_FIN:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE offrelocations SET lieu_fin = '%s' WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                             );
                break;
            case PRIX:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE offrelocations SET prix_caution = %lf WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                             );
                break;
            default:
                break;
            };
        }
    );
}

ViewListOffreLocation::~ViewListOffreLocation()
{
    delete ui;
}
