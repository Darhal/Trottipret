#include "trottinette.h"

// constructeur normale
Trottinette::Trottinette(const QString& model, unsigned int ref, const QString& etat)
    : m_Model(model), m_Etat(etat), m_Image(), m_Ref(ref)
{
}

// move constructeur, qui utilise std::move pour effectuer une move et pas une copie !!!
Trottinette::Trottinette(Trottinette&& other) :
    m_Model(std::move(other.m_Model)), m_Etat(std::move(other.m_Etat)),
    m_Image(std::move(other.m_Image)), m_Ref(other.m_Ref)
{
}
