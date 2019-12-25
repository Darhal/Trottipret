#include "viewmyprofile.h"
#include "ui_viewmyprofile.h"

ViewMyProfile::ViewMyProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewMyProfile)
{
    ui->setupUi(this);
}

ViewMyProfile::~ViewMyProfile()
{
    delete ui;
}
