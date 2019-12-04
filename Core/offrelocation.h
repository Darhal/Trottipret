#ifndef OFFRELOCATION_H
#define OFFRELOCATION_H

#include <QDateTime>
#include <QString>
#include "Core/trottinette.h"

/**
 * @class OffreLocation
 * @brief Classe OffreLocation qui represente les offres de location proposées par les propriétaires
*/
class OffreLocation
{
public:
    /**
     * @fn OffreLocation
     * @brief Constructeur par defaut
    */
    OffreLocation(){}

    /**
     * @fn OffreLocation
     * @brief constructeur de copie
     * @param const OffreLocation& other
    */
    OffreLocation(const OffreLocation& other);

    /**
     * @fn OffreLocation
     * @brief Constructeur
     * @param Trottinette* trotti
     * @param double prix
     * @param const QDateTime dates[2]
     * @param const QString lieux[2]
    */
    OffreLocation(Trottinette* trotti, double prix, const QDateTime dates[2], const QString lieux[2]);

    // Respect des principes de programmation orienté objet : encapsulations
    /**
     * @fn SetTrottinette
     * @brief Des setteurs inline c'est très rapide
     * @param Trottinette* trotti
    */
    inline void SetTrottinette(Trottinette* t) { m_Trottinette = t; }
    /**
     * @fn SetDateDebut
     * @brief Setteur
     * @param const QDateTime& dates
    */
    inline void SetDateDebut(const QDateTime& d) { m_Dates[DEBUT_INDEX] = d; }
    /**
     * @fn SetDateFin
     * @brief Setteur
     * @param const QDateTime& dates
    */
    inline void SetDateFin(const QDateTime& d) { m_Dates[FIN_INDEX] = d; }
    /**
     * @fn SetLieuRetrait
     * @brief Setteur
     * @param double prix
     * @param const QString& lieux
    */
    inline void SetLieuRetrait(const QString& l) { m_Lieux[DEBUT_INDEX] = l; }
    /**
     * @fn SetLieuRetour
     * @brief Setteur
     * @param const QString& lieux
    */
    inline void SetLieuRetour(const QString& l) { m_Lieux[FIN_INDEX] = l; }
    /**
     * @fn SetPrixCaution
     * @brief Setteur
     * @param double prix
    */
    inline void SetPrixCaution(double p) { m_PrixCaution = p; }

    // Des getteurs inline c'est très rapide
    // Respect des principes de programmation orienté objet : encapsulations
    /**
     * @fn GetTrottinette
     * @brief Des getteurs inline c'est très rapide
     * @return Trottinette
    */
    inline Trottinette* GetTrottinette() const { return m_Trottinette ; }
    /**
     * @fn GetDateDebut
     * @brief Des getteurs inline c'est très rapide
     * @return const QDateTime&
    */
    inline const QDateTime& GetDateDebut() const { return m_Dates[DEBUT_INDEX]; }
    /**
     * @fn GetDateFin
     * @brief Des getteurs inline c'est très rapide
     * @return const QDateTime&
    */
    inline const QDateTime& GetDateFin() const { return m_Dates[FIN_INDEX]; }
    /**
     * @fn GetLieuRetrait
     * @brief Des getteurs inline c'est très rapide
     * @return const QString&
    */
    inline const QString& GetLieuRetrait() const { return m_Lieux[DEBUT_INDEX]; }
    /**
     * @fn GetLieuRetour
     * @brief Des getteurs inline c'est très rapide
     * @return const QString&
    */
    inline const QString& GetLieuRetour() const { return m_Lieux[FIN_INDEX] ; }
    /**
     * @fn GetPrixCaution
     * @brief Des getteurs inline c'est très rapide
     * @return double prix
    */
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
