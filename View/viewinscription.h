#ifndef VIEWINSCRIPTION_H
#define VIEWINSCRIPTION_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class ViewInscription;
}


/**
 * @class ViewInscription
 * @brief Classe qui represente la boite de Dialogue d'inscription
 * Elle herite de QDialog
*/
class ViewInscription : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn Constructeur de ViewInscription
     * @param  QWidget* parent
     * @return rien
    */
    explicit ViewInscription(QWidget *parent = nullptr);
    
    /**
     * @fn Destructeur de ViewInscription
    */

    ~ViewInscription();

    /**
     * @fn VerifySignupInformations
     * @brief verification des donnees de l'inscription
     * @return bool
    */
    bool VerifySignupInformations();

    /**
     * @fn FinishSignup
     * @brief  faire l'inscription
    */
    void FinishSignup();
private slots:
    void on_buttonBox_accepted();

    /**
     * @fn accept
     * @brief  les slots, on surcharge la fonction accept pour ne pas
     * supprimer la fenêtre lorsque les
     * informations ne sont pas bonnes
    */
    void accept() override; 

private:
    Ui::ViewInscription *ui;
};

#endif // VIEWINSCRIPTION_H
