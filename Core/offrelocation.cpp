#include "offrelocation.h"

// Constructeur
OffreLocation::OffreLocation(Trottinette* trotti, double prix,
                                           const QDateTime dates[2], const QString lieux[2]) :
    m_Trottinette(trotti), m_PrixCaution(prix) // Initialisation de trotti et prix caution
{
    // Initialisation de lieux retrait, depot, date de fin et de debut
    for(int  i = 0; i <= OffreLocation::FIN_INDEX; i++){
           m_Dates[i] = dates[i];
           m_Lieux[i] = lieux[i];
    }
}

// Constructeur de copie
OffreLocation::OffreLocation(const OffreLocation& other) :
     m_Trottinette(other.m_Trottinette), m_PrixCaution(other.m_PrixCaution)
 {
     // Initialisation de lieux retrait, depot, date de fin et de debut
     for(int  i = 0; i <= OffreLocation::FIN_INDEX; i++){
            m_Dates[i] = std::move(other.m_Dates[i]);
            m_Lieux[i] = std::move(other.m_Lieux[i]);
     }
 }
