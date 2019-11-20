#ifndef TROTTINETTE_H
#define TROTTINETTE_H

#include <QString>
#include <QImage>

class Trottinette
{
public:
    Trottinette(const QString& model, unsigned int ref, const QString& etat);

    Trottinette(Trottinette&& other); // Move ctor
private:
    QString m_Model, m_Etat;
    QImage m_Image;
    unsigned int m_Ref;
};

#endif // TROTTINETTE_H
