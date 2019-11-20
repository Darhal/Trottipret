#ifndef PROPRIETAIRE_H
#define PROPRIETAIRE_H

#include "Core/offrelocation.h"
#include <vector>

class Proprietaire
{
public:
    Proprietaire();

    inline void ajouterOffre(const OffreLocation& offre) { m_Locations.emplace_back(offre); }

    inline const std::vector<OffreLocation>& GetOffreLocation() const { return m_Locations; }
private:
    std::vector<OffreLocation> m_Locations;
};

#endif // PROPRIETAIRE_H
