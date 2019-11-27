#include "viewinscription.h"
#include "ui_viewinscription.h"
#include <QKeyEvent>

ViewInscription::ViewInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewInscription)

{
    ui->setupUi(this);
}

void ViewInscription::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        QString mdp = ui->mdp->placeholderText();
        QString adrmail = ui->mdp->placeholderText();
        QString prenom = ui->mdp->placeholderText();
        QString nom = ui->mdp->placeholderText();
        QString identifiant = ui->mdp->placeholderText();
        ui->warning->setText("Erreur lors de la saisie des champ ou compte deja utiliser");
    }
}


ViewInscription::~ViewInscription()
{
    delete ui;
}
