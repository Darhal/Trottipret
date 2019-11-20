#include "utilisateur.h"

Utilisateur::Utilisateur(const QString& identifiant, const QString& mail) :
    Proprietaire(),
    m_Identifiant(identifiant), m_AdresseMail(mail)
{

}
