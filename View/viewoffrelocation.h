#ifndef VIEWOFFRELOCATION_H
#define VIEWOFFRELOCATION_H

#include <QDialog>

namespace Ui {
class ViewOffreLocation;
}


/*
 * Classe qui represente la boite de Dialogue d'offre de location
 * Elle herite de QDialog
*/
class ViewOffreLocation : public QDialog
{
    Q_OBJECT

public:
    explicit ViewOffreLocation(QWidget *parent = 0); // constructeur

    ~ViewOffreLocation(); //destructeur

    bool VerifyData(); // Verification des donnees du formulaire

    void SubmitOffre();

private slots:
    void accept() override; // les slots, on surcharge la fonction accept pour ne pas
                            // supprimer la fenêtre lorsque les
                            // informations ne sont pas bonnes

private:
    Ui::ViewOffreLocation* ui;
    QString m_ImageFilePath;
};

#endif // VIEWOFFRELOCATION_H
