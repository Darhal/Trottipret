#include "utilisateur.h"

// Constructeur normal
Utilisateur::Utilisateur(const QString& identifiant, const QString& mail) :
    Proprietaire(),
    m_Identifiant(identifiant), m_AdresseMail(mail)
{
}
