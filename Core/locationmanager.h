#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include "Core/trottinette.h"
#include "Core/utilisateur.h"
#include "Core/offrelocation.h"


/*
Classe LocationManager qui gère les propositions de location et son modèle de conception SIngelton
*/
class LocationManager
{
public:
    // Recuperer l'instance
    static LocationManager& GetInstance();

    // Pour ajouter les offre de location a un user
    void AjouterOffreLocation(Utilisateur& user, const OffreLocation& offre);
private:
    static LocationManager s_Instance; // Note instance

    LocationManager(); // Constructeur privé
};

#endif // LOCATIONMANAGER_H
