#ifndef VIEWINSCRIPTION_H
#define VIEWINSCRIPTION_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class ViewInscription;
}

/*
 * Classe qui represente la boite de Dialogue d'inscription
 * Elle herite de QDialog
*/
class ViewInscription : public QDialog
{
    Q_OBJECT

public:
    explicit ViewInscription(QWidget *parent = 0); // constructeur
    ~ViewInscription(); // destructeur
    bool VerifySignupInformations(); // verification des donnees de l'inscription

    void FinishSignup(); // faire l'inscription
private slots:
    void on_buttonBox_accepted();
    void accept() override; // les slots, on surcharge la fonction accept pour ne pas
                            // supprimer la fenêtre lorsque les
                            // informations ne sont pas bonnes

private:
    Ui::ViewInscription *ui;
};

#endif // VIEWINSCRIPTION_H
