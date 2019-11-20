#ifndef PROPRIETAIRE_H
#define PROPRIETAIRE_H

#include "Core/offrelocation.h"
#include <vector>

class Proprietaire
{
public:
    Proprietaire();


    inline OffreLocation& ajouterOffre() {
        m_Locations.emplace_back();
        return m_Locations.back();
    }

    inline const std::vector<OffreLocation>& GetOffreLocation() const { return m_Locations; }
private:
    std::vector<OffreLocation> m_Locations;
};

#endif // PROPRIETAIRE_H
