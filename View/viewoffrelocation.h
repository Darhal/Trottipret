#ifndef VIEWOFFRELOCATION_H
#define VIEWOFFRELOCATION_H

#include <QDialog>

namespace Ui {
class ViewOffreLocation;
}


/**
 * @class ViewOffreLocation
 * @brief Classe qui represente la boite de Dialogue d'offre de location
 * Elle herite de QDialog
*/
class ViewOffreLocation : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn Constructeur de ViewOffreLocation
     * @param  QWidget* parent
     * @return rien
    */
    explicit ViewOffreLocation(QWidget *parent = 0); // constructeur

    /**
     * @fn Destructor de ViewOffreLocation
    */
    ~ViewOffreLocation(); //destructeur

private:
    Ui::ViewOffreLocation* ui;
};

#endif // VIEWOFFRELOCATION_H
