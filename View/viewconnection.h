#ifndef VIEWCONNECTION_H
#define VIEWCONNECTION_H

#include <QDialog>

namespace Ui {
class ViewConnection;
}

/*
 * Classe qui represente la boite de Dialogue de login
 * Ca herite de QDialog
*/
class ViewConnection : public QDialog
{
    Q_OBJECT

public:
    // Constructeur
    explicit ViewConnection(QWidget *parent = 0);

    // Fonction qui verifie les informations de login
    bool VerifyLoginInformations();

    // Fonction qui effectue le login
    void FinishLogin();

    // Destructeur
    ~ViewConnection();

private slots:
    void accept() override; // les slots on surcharge la fonction accept pour ne pas
                            // supprimer la fentre lorsque les
                            // identifiants ne sont pas bon

private:
    Ui::ViewConnection *ui;
};

#endif // VIEWCONNECTION_H
