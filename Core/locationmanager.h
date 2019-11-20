#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include "Core/trottinette.h"
#include "Core/utilisateur.h"
#include "Core/offrelocation.h"

class LocationManager
{
public:
    LocationManager();

    static LocationManager& GetInstance();

    void AjouterOffreLocation(Utilisateur& user, const OffreLocation& offre);
private:
    static LocationManager s_Instance;
};

#endif // LOCATIONMANAGER_H
