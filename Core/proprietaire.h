#ifndef PROPRIETAIRE_H
#define PROPRIETAIRE_H

#include "Core/offrelocation.h"
#include <vector>

/**
 * @class Proprietaire
 * @brief Classe qui represente le proprietaire
*/
class Proprietaire
{
public:
    /**
     * @fn Proprietaire
     * @brief Constructeur par defaut
    */
    Proprietaire(); // constructeur

    /**
     * @fn ajouterOffre
     * @brief fonction inline qui ajoute les offres de locations
     * @param const OffreLocation& offre
    */
    inline void ajouterOffre(const OffreLocation& offre) { m_Locations.emplace_back(offre); }

    // fonction inline qui recupere les offres de locations

    /**
     * @fn GetOffreLocation
     * @brief fonction inline qui recupere les offres de locations
     * @return const std::vector<OffreLocation>&
    */
    inline const std::vector<OffreLocation>& GetOffreLocation() const { return m_Locations; }
private:
    std::vector<OffreLocation> m_Locations;
};

#endif // PROPRIETAIRE_H
