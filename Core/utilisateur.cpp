#include "utilisateur.h"

// Constructeur normal
Utilisateur::Utilisateur(const QString& identifiant = "anonyme",
                         const QString& mail = "anonyme@anonyme.com",
                         const QString& nom = "anonyme",
                         const QString& prenom = "anonyme",
                         const QString& mdp = "0",) :
    Proprietaire(),
    m_Identifiant(identifiant), m_AdresseMail(mail), m_Nom(nom),
    m_Prenom(prenom), m_Mdp(mdp)
{
}
