#ifndef VIEWCONNECTION_H
#define VIEWCONNECTION_H

#include <QDialog>

namespace Ui {
class ViewConnection;
}


/**
 * @class ViewConnection
 * @brief Classe qui represente la boite de Dialogue de login
 * Elle herite de QDialog
*/
class ViewConnection : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn Constructeur de ViewOffreLocation
     * @param  QWidget* parent
     * @return rien
    */
    explicit ViewConnection(QWidget *parent = 0);

    /**
     * @fn Fonction qui verifie les informations de login
     * @return bool
    */
    bool VerifyLoginInformations();

    /**
     * @fn Fonction qui effectue le login
    */
    void FinishLogin();

    /**
     * @fn Destructeur
    */
    ~ViewConnection();

private slots:
    /**
     * @fn accept
     * @brief les slots, on surcharge la fonction accept pour ne pas
     * supprimer la fenêtre lorsque les
     * identifiants ne sont pas bons
     * @return void
    */
    void accept() override;

private:
    Ui::ViewConnection *ui;
};

#endif // VIEWCONNECTION_H
