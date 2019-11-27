#ifndef VIEWOFFRELOCATION_H
#define VIEWOFFRELOCATION_H

#include <QDialog>

class ViewOffreLocation : public QDialog
{
    Q_OBJECT
public:
    explicit ViewOffreLocation(QWidget* parent = nullptr);

    void OnAjouterOffre();
signals:

public slots:
};

#endif // VIEWOFFRELOCATION_H
