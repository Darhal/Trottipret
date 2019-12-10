#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include "Core/trottinette.h"
#include "Core/utilisateur.h"
#include "Core/offrelocation.h"


/**
* @class LocationManager
* @brief Classe LocationManager qui gère les propositions de location et son modèle de conception Singleton
*/
class LocationManager
{
public:
    /**
     * @fn GetInstance
     * @brief Fonction statique qui va retourner l'instance de notre singleton
     * @return LocationManager&
    */
    static LocationManager& GetInstance();

    /**
     * @fn AjouterOffreLocation
     * @brief Pour ajouter les offres de location à un utilisateur
     * @param Utilisateur& user 
     * @param const OffreLocation& offre
     * @return void
    */
    void AjouterOffreLocation(Utilisateur& user, const OffreLocation& offre);
private:
    static LocationManager s_Instance; // Notre instance

    LocationManager(); // Constructeur privé
};

#endif // LOCATIONMANAGER_H
