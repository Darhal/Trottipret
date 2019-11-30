#include "locationmanager.h"
#include "databasemanager.h"

// Intilization de notre variable statique, il faut que ce soit obligatoirement dans le .cpp
// D'apres touts les standards C++!
LocationManager LocationManager::s_Instance;

LocationManager::LocationManager() //  constructeur
{

}

// Recupere la var statique
LocationManager& LocationManager::GetInstance()
{
    return LocationManager::s_Instance;
}

void LocationManager::AjouterOffreLocation(Utilisateur& user, const OffreLocation& offre)
{
    user.ajouterOffre(offre); // ajoute l'offre
    // DatabaseManager::GetInstance().Exec(); // N'est pas disponnible pour le moment dans les version procheaines
}
