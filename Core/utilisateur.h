#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include "Core/proprietaire.h"

/*
 * Classe qui represente l'Utilisateur qui herite de Proprietaire
 * Parceque un utlisateur peut etre un Proprietaire et un Locataire dans notre appli
*/
class Utilisateur : public Proprietaire
{
public:
    // Constructeur avec des arguments par default
    Utilisateur(const QString& identifiant = "anonyme", const QString& mail = "anonyme@anonyme.com");

    // Getteur qui recupere l' identifiant
    const QString& GetIdentifiant() { return m_Identifiant; }
private:
    // Les champs
    const QString m_Identifiant;
    QString m_Nom, m_Prenom, m_AdresseMail, m_Mdp;

};

#endif // UTILISATEUR_H
