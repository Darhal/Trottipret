#include "offrelocation.h"

// Constructeur
OffreLocation::OffreLocation(Trottinette* trotti, double prix,
                                           const QDateTime dates[2], const QString lieux[2]) :
    m_Trottinette(trotti), m_PrixCaution(prix) // intilization de trotti et prix caution
{
    // intilizatino de lieux retrait depot date fin et debut
    for(int  i = 0; i <= OffreLocation::FIN_INDEX; i++){
           m_Dates[i] = dates[i];
           m_Lieux[i] = lieux[i];
    }
}

// COnstructeur de copie
OffreLocation::OffreLocation(const OffreLocation& other) :
     m_Trottinette(other.m_Trottinette), m_PrixCaution(other.m_PrixCaution)
 {
     // intilizatino de lieux retrait depot date fin et debut
     for(int  i = 0; i <= OffreLocation::FIN_INDEX; i++){
            m_Dates[i] = std::move(other.m_Dates[i]);
            m_Lieux[i] = std::move(other.m_Lieux[i]);
     }
 }
