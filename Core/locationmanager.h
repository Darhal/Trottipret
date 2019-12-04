#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include "Core/trottinette.h"
#include "Core/utilisateur.h"
#include "Core/offrelocation.h"


/*
Classe LocationManager qui gère les propositions de location et son modèle de conception Singleton
*/
class LocationManager
{
public:
    // Recupere l'instance
    static LocationManager& GetInstance();

    // Pour ajouter les offres de location à un utilisateur
    void AjouterOffreLocation(Utilisateur& user, const OffreLocation& offre);
private:
    static LocationManager s_Instance; // Notre instance

    LocationManager(); // Constructeur privé
};

#endif // LOCATIONMANAGER_H
