#include "viewoffrelocation.h"
#include "ui_viewoffrelocation.h"

// Constructeur
ViewOffreLocation::ViewOffreLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewOffreLocation)
{
    ui->setupUi(this);
}

void ViewOffreLocation::VerifyInformations()
{

}

void ViewOffreLocation::SubmitOffre()
{

}


// Destructeur
ViewOffreLocation::~ViewOffreLocation()
{
    delete ui;
}
