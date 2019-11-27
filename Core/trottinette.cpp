#include "trottinette.h"

Trottinette::Trottinette(const QString& model, unsigned int ref, const QString& etat)
    : m_Model(model), m_Ref(ref), m_Etat(etat)
{
}

Trottinette::Trottinette(Trottinette&& other) :
    m_Model(std::move(other.m_Model)), m_Etat(std::move(other.m_Etat)),
    m_Ref(other.m_Ref), m_Image(std::move(other.m_Image))
{
}
