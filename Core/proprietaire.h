#ifndef PROPRIETAIRE_H
#define PROPRIETAIRE_H

#include "Core/offrelocation.h"
#include <vector>

/*
 * Classe qui represente le proprietaire
*/
class Proprietaire
{
public:
    Proprietaire(); // constructeur

    // fonction inline qui ajoute les offres de locations
    inline void ajouterOffre(const OffreLocation& offre) { m_Locations.emplace_back(offre); }

    // fonction inline qui recupere les offres de locations
    inline const std::vector<OffreLocation>& GetOffreLocation() const { return m_Locations; }
private:
    std::vector<OffreLocation> m_Locations;
};

#endif // PROPRIETAIRE_H
