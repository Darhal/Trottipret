#ifndef OFFRELOCATION_H
#define OFFRELOCATION_H

#include <QDateTime>
#include <QString>
#include "Core/trottinette.h"

/*
 * Classe OffreLocation qui represente les offres de location proposées par les propriétaires
*/
class OffreLocation
{
public:
    OffreLocation(){}

    OffreLocation(const OffreLocation& other);

    OffreLocation(Trottinette* trotti, double prix, const QDateTime dates[2], const QString lieux[2]);

    // Des setteurs inline c'est très rapide
    // Respect des principes de programmation orienté objet : encapsulations
    inline void SetTrottinette(Trottinette* t) { m_Trottinette = t; }
    inline void SetDateDebut(const QDateTime& d) { m_Dates[DEBUT_INDEX] = d; }
    inline void SetDateFin(const QDateTime& d) { m_Dates[FIN_INDEX] = d; }
    inline void SetLieuRetrait(const QString& l) { m_Lieux[DEBUT_INDEX] = l; }
    inline void SetLieuRetour(const QString& l) { m_Lieux[FIN_INDEX] = l; }
    inline void SetPrixCaution(double p) { m_PrixCaution = p; }

    // Des getteurs inline c'est très rapide
    // Respect des principes de programmation orienté objet : encapsulations
    inline Trottinette* GetTrottinette() const { return m_Trottinette ; }
    inline const QDateTime& GetDateDebut() const { return m_Dates[DEBUT_INDEX]; }
    inline const QDateTime& GetDateFin() const { return m_Dates[FIN_INDEX]; }
    inline const QString& GetLieuRetrait() const { return m_Lieux[DEBUT_INDEX]; }
    inline const QString& GetLieuRetour() const { return m_Lieux[FIN_INDEX] ; }
    inline double GetPrixCaution() const { return m_PrixCaution; }
private:
    // Des variables definies dans le temps de compilation qui indique les index de debut et fin.
    constexpr static unsigned char DEBUT_INDEX = 0;
    constexpr static unsigned char FIN_INDEX = DEBUT_INDEX + 1;

    Trottinette* m_Trottinette; // Pointeur vers une trottinette
    QDateTime m_Dates[2]; // 2 dates debut et fin respectivement avec l'index 0 et 1
    QString m_Lieux[2]; // 2 lieux retrait et depot respectivement avec l'index 0 et 1
    double m_PrixCaution; // prix caution
};

#endif // OFFRELOCATION_H
