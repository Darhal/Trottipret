#include "viewlistoffrelocation.h"
#include "ui_viewlistoffrelocation.h"
#include "Core/applicationmanager.h"
#include "Core/databasemanager.h"
#include <qdebug.h>
#include <QTimer>
#include <QMessageBox>

ViewListOffreLocation::ViewListOffreLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewListOffreLocation)
{
    ui->setupUi(this);
    ui->tableOffLoc->verticalHeader()->hide();
    ui->tableOffLoc->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->tableOffLoc->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->info->setWordWrap(true);
    this->RefreshList();

    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    connect(ui->delete_2, &QPushButton::clicked, this, [this](){
        QModelIndex index = ui->tableOffLoc->currentIndex();
        QString ref = ui->tableOffLoc->item(index.row(), 0)->text();
        Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();

        if (cur_user!=NULL){
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Etes-vous sur que vous voulez supprimer l'offre de location ?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                DatabaseManager::GetInstance()
                        .Exec("DELETE FROM locations WHERE ref_trotti='%s' AND identifiant='%s';",
                                ref.toLocal8Bit().constData(), cur_user->GetIdentifiant().toLocal8Bit().constData()
                             );
                ui->info->setStyleSheet("color:green;");
                ui->info->setText("INFORMATIONS: Offre Location deleted sucessfully.");
                //QTimer::singleShot(200, this, SLOT([this](){ui->info->setText("");}));
                this->RefreshList();
            }
        }
    });
    connect(ui->tableOffLoc, &QTableWidget::itemChanged, this,
        [this](QTableWidgetItem*item){
            QString ref = ui->tableOffLoc->item(item->row(), REF)->text();
            QString updated_text = item->text();
            QString idf = ApplicationManager::GetInstance().GetCurrentUser()->GetIdentifiant();

            switch((Cols)item->column()){
            case REF:
                break;
            case DATE_DEBUT:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE locations SET date_debut = '%s' WHERE ref_trotti='%s' AND identifiant='%s' ;",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                             );
                break;
            case DATE_FIN:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE locations SET date_fin = '%s' WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                              );
                break;
            case LIEU_DEBUT:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE locations SET lieu_debut = '%s' WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                              );
                break;
            case LIEU_FIN:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE locations SET lieu_fin = '%s' WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                             );
                break;
            case PRIX:
                DatabaseManager::GetInstance()
                        .Exec("UPDATE locations SET prix_caution = %lf WHERE ref_trotti='%s' AND identifiant='%s';",
                                updated_text.toLocal8Bit().constData(), ref.toLocal8Bit().constData(), idf.toLocal8Bit().constData()
                             );
                break;
            default:
                break;
            };
        }
    );
}

void ViewListOffreLocation::RefreshList()
{
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();
    ui->tableOffLoc->setRowCount(0);

    if (cur_user != NULL){
        QSqlQuery r = std::move(DatabaseManager::GetInstance()
                .Exec("SELECT * FROM locations WHERE identifiant = '%s' AND locataire is NULL;", cur_user->GetIdentifiant().toLocal8Bit().constData()));

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
}

ViewListOffreLocation::~ViewListOffreLocation()
{
    delete ui;
}
