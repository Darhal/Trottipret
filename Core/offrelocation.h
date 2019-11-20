#ifndef OFFRELOCATION_H
#define OFFRELOCATION_H

#include <QDateTime>
#include <QString>
#include "Core/trottinette.h"

class OffreLocation
{
public:
    OffreLocation(){}

    OffreLocation(Trottinette* trotti, double prix, const QDateTime dates[2], const QString lieux[2]);

    inline void SetTrottinette(Trottinette* t) { m_Trottinette = t; }
    inline void SetDateDebut(const QDateTime& d) { m_Dates[DEBUT_INDEX] = d; }
    inline void SetDateFin(const QDateTime& d) { m_Dates[FIN_INDEX] = d; }
    inline void SetLieuRetrait(const QString& l) { m_Lieux[DEBUT_INDEX] = l; }
    inline void SetLieuRetour(const QString& l) { m_Lieux[FIN_INDEX] = l; }
    inline void SetPrixCaution(double p) { m_PrixCaution = p; }

    inline Trottinette* GetTrottinette() const { return m_Trottinette ; }
    inline const QDateTime& GetDateDebut() const { return m_Dates[DEBUT_INDEX]; }
    inline const QDateTime& GetDateFin() const { return m_Dates[FIN_INDEX]; }
    inline const QString& GetLieuRetrait() const { return m_Lieux[DEBUT_INDEX]; }
    inline const QString& GetLieuRetour() const { return m_Lieux[FIN_INDEX] ; }
    inline double GetPrixCaution() const { return m_PrixCaution; }
private:
    constexpr static unsigned char DEBUT_INDEX = 0;
    constexpr static unsigned char FIN_INDEX = DEBUT_INDEX + 1;

    Trottinette* m_Trottinette;
    QDateTime m_Dates[2];
    QString m_Lieux[2];
    double m_PrixCaution;
};

#endif // OFFRELOCATION_H
