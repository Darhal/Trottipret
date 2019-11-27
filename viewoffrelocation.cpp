#include "viewoffrelocation.h"
#include "ui_viewoffrelocation.h"

ViewOffreLocation::ViewOffreLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewOffreLocation)
{
    ui->setupUi(this);
}

ViewOffreLocation::~ViewOffreLocation()
{
    delete ui;
}
