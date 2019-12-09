#include "viewlisteoffre.h"
#include "ui_viewlisteoffre.h"

ViewListeOffre::ViewListeOffre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewListeOffre)
{
    ui->setupUi(this);
}

ViewListeOffre::~ViewListeOffre()
{
    delete ui;
}
