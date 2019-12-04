#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include "Core/proprietaire.h"

/**
 * @class Utilisateur
 * @brief Classe qui represente l'Utilisateur qui herite de Proprietaire
 * Car un utlisateur peut etre un Proprietaire et un Locataire dans notre application
*/
class Utilisateur : public Proprietaire
{
public:
    /**
     * @fb Utilisateur
     * @brief Constructeur avec des arguments par defaut
    */
    Utilisateur(const QString& identifiant = "anonyme", const QString& mail = "anonyme@anonyme.com");

    /**
     * @fb Utilisateur
     * @brief Getteur qui recupere l' identifiant
     * @return const QString&
    */
    const QString& GetIdentifiant() { return m_Identifiant; }
private:
    // Les champs
    const QString m_Identifiant;
    QString m_Nom, m_Prenom, m_AdresseMail, m_Mdp;

};

#endif // UTILISATEUR_H
