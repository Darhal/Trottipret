#ifndef TROTTINETTE_H
#define TROTTINETTE_H

#include <QString>
#include <QImage>

/**
 * @class Trottinette
 * @brief Classe qui represente la Trottinette
*/
class Trottinette
{
public:
    /**
     * @fn Trottinette
     * @brief Constructeur qui prend le model, la reference et l'etat
     * @param const QString& model
     * @param unsigned int ref
     * @param const QString& etat
    */
    Trottinette(const QString& model, unsigned int ref, const QString& etat);

    /**
     * @fn Trottinette
     * @brief Move constructeur qui sera plus rapide que le constructeur de copie
     * puisque cela copie juste les pointeusr et pas les donnees
     * Principe de move constructeur: https://en.cppreference.com/w/cpp/language/move_constructor
     * @param Trottinette&& other
    */
    Trottinette(Trottinette&& other);
private:
    // Les champs
    QString m_Model, m_Etat;
    QImage m_Image;
    unsigned int m_Ref;
};

#endif // TROTTINETTE_H
