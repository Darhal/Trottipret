#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include "Core/proprietaire.h"

class Utilisateur : public Proprietaire
{
public:
    Utilisateur(const QString& identifiant = "anonyme", const QString& mail = "anonyme@anonyme.com");
    const QString& GetIdentifiant() { return m_Identifiant; }
private:
    const QString m_Identifiant;
    QString m_Nom, m_Prenom, m_AdresseMail, m_Mdp;

};

#endif // UTILISATEUR_H
