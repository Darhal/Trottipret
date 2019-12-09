#include "utilisateur.h"

// Constructeur normal
Utilisateur::Utilisateur(const QString& identifiant,
                         const QString& mail,
                         const QString& nom,
                         const QString& prenom,
                         const QString& mdp) :
    Proprietaire(),
    m_Identifiant(identifiant), m_AdresseMail(mail), m_Nom(nom),
    m_Prenom(prenom), m_Mdp(mdp)
{
}
