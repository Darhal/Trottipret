#ifndef VIEWOFFRELOCATION_H
#define VIEWOFFRELOCATION_H

#include <QDialog>

namespace Ui {
class ViewOffreLocation;
}


/*
 * Classe qui represente la boite de Dialogue d'offre de location
 * Ca herite de QDialog
*/
class ViewOffreLocation : public QDialog
{
    Q_OBJECT

public:
    explicit ViewOffreLocation(QWidget *parent = 0); // constructeur
    ~ViewOffreLocation(); //destructeur

private:
    Ui::ViewOffreLocation* ui;
};

#endif // VIEWOFFRELOCATION_H
