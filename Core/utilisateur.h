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
    Utilisateur(const QString& identifiant = "anonyme",
                const QString& mail = "anonyme@anonyme.com",
                const QString& nom = "anonyme",
                const QString& prenom = "anonyme",
                const QString& mdp = "0"
            );

    /**
     * @fb Utilisateur
     * @brief Getteur qui recupere l' identifiant
     * @return const QString&
    */
    const QString& GetIdentifiant() const { return m_Identifiant; }


    /**
     * @fb Utilisateur
     * @brief Getteur qui recupere l'AdresseMail
     * @return const QString&
    */
    const QString& GetAdresseMail() const { return m_AdresseMail; }

    /**
     * @fb Utilisateur
     * @brief Getteur qui recupere le nom
     * @return const QString&
    */
    const QString& GetNom() const { return m_Nom; }

    /**
     * @fb Utilisateur
     * @brief Getteur qui recupere le prenom
     * @return const QString&
    */
    const QString& GetPrenom() const { return m_Prenom; }

    /**
     * @fb Utilisateur
     * @brief Getteur qui recupere le mdp
     * @return const QString&
    */
    const QString& GetMdp() const { return m_Mdp; }

    /**
     * @fb Utilisateur
     * @brief Setteur Email
     * @arg const QString&
     * @return void
    */
    void SetAdresseMail(const QString& mail){ m_AdresseMail = mail;}

    /**
     * @fb Utilisateur
     * @brief Setteur Nom
     * @arg const QString&
     * @return void
    */
    void SetNom(const QString& n){ m_Nom = n;}

    /**
     * @fb Utilisateur
     * @brief Setteur Prenom
     * @arg const QString&
     * @return void
    */
    void SetPrenom(const QString& p){ m_Prenom = p;}

    /**
     * @fb Utilisateur
     * @brief Setteur Mdp
     * @arg const QString&
     * @return void
    */
    void SetMdp(const QString& mdp){ m_Mdp = mdp;}

private:
    // Les champs
    const QString m_Identifiant;
    QString m_AdresseMail, m_Nom, m_Prenom, m_Mdp;

};

#endif // UTILISATEUR_H
