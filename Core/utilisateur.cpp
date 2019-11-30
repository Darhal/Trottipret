#include "utilisateur.h"

// Constructeur normale
Utilisateur::Utilisateur(const QString& identifiant, const QString& mail) :
    Proprietaire(),
    m_Identifiant(identifiant), m_AdresseMail(mail)
{
}
