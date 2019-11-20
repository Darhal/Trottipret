#include "locationmanager.h"

LocationManager LocationManager::s_Instance;

LocationManager::LocationManager()
{

}

LocationManager& LocationManager::GetInstance()
{
    return LocationManager::s_Instance;
}

void LocationManager::AjouterOffreLocation(Utilisateur& user, const OffreLocation& offre)
{
    user.ajouterOffre(offre);
}
