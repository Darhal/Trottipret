#include "viewlistetrottinette.h"
#include "ui_viewlistetrottinette.h"
#include <Core/databasemanager.h>
#include <Core/applicationmanager.h>
#include <qdebug.h>

ViewListeTrottinette::ViewListeTrottinette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewListeTrottinette)
{
    ui->setupUi(this);
    ui->listTrotti->verticalHeader()->hide();
    ui->listTrotti->setSelectionBehavior((QAbstractItemView::SelectRows));
    ui->listTrotti->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    Utilisateur* cur_user = ApplicationManager::GetInstance().GetCurrentUser();
    if (cur_user != NULL){
        QSqlQuery& r = DatabaseManager::GetInstance()
                .Exec("SELECT * FROM trottinettes WHERE identifiant='%s';", cur_user->GetIdentifiant().toLocal8Bit().constData());
        while (r.next()){
            int row_count = ui->listTrotti->rowCount();
            ui->listTrotti->insertRow(row_count);

            for(int i = 0; i < 3; i++){
                ui->listTrotti->setItem(row_count, i, new QTableWidgetItem(r.value(i).toString()));
            }
        }
    }

    connect(ui->listTrotti, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnRowSelection()));
    connect(ui->fermer, &QPushButton::clicked, this, [this](){this->close();});
    connect(ui->listTrotti, &QTableWidget::itemChanged, this,
        [this](QTableWidgetItem*item){
            qDebug() << "Item changed (C:" << item->column() << "L:" << item->row();
        }
    );
}

void ViewListeTrottinette::OnRowSelection()
{
    QModelIndex index = ui->listTrotti->currentIndex();
    int i = index.row();
    QString ref = ui->listTrotti->item(i, 0)->text();

    /*for (int ic = 0; ic < ui->listTrotti->columnCount(); ic++){
        ui->listTrotti->item(i, ic)->setSelected(true);
    }*/

    qDebug() << ref;
    QSqlQuery& r = DatabaseManager::GetInstance()
            .Exec("SELECT image FROM trottinettes WHERE ref_trotti = '%s';", ref.toLocal8Bit().constData());
    if (r.first()){
        QByteArray image_bytes = r.value(0).toByteArray();
        QPixmap img_pixmap = QPixmap();
        img_pixmap.loadFromData( std::move(image_bytes) );
        ui->imageTrotti->setPixmap(img_pixmap);
    }
}

ViewListeTrottinette::~ViewListeTrottinette()
{
    delete ui;
}
