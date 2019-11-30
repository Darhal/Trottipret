#ifndef VIEWINSCRIPTION_H
#define VIEWINSCRIPTION_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class ViewInscription;
}

/*
 * Classe qui represente la boite de Dialogue d'inscription
 * Ca herite de QDialog
*/
class ViewInscription : public QDialog
{
    Q_OBJECT

public:
    explicit ViewInscription(QWidget *parent = 0); // constructeur
    ~ViewInscription(); // destrcuteur
    bool VerifySignupInformations(); // verification des donnes de l'inscription

    void FinishSignup(); // faire l'inscription
private slots:
    void on_buttonBox_accepted();
    void accept() override; // les slots on surcharge la fonction accept pour ne pas
                            // supprimer la fentre lorsque les
                            // informations ne sont pas bon

private:
    Ui::ViewInscription *ui;
};

#endif // VIEWINSCRIPTION_H
