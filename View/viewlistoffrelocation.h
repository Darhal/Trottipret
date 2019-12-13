#ifndef VIEWLISTOFFRELOCATION_H
#define VIEWLISTOFFRELOCATION_H

#include <QDialog>

namespace Ui {
class ViewListOffreLocation;
}

class ViewListOffreLocation : public QDialog
{
    Q_OBJECT

    enum Cols {
        REF = 0,
        DATE_DEBUT = 1,
        DATE_FIN = 2,
        LIEU_DEBUT = 3,
        LIEU_FIN = 4,
        PRIX = 5
    };

public:
    explicit ViewListOffreLocation(QWidget *parent = 0);
    ~ViewListOffreLocation();

private:
    Ui::ViewListOffreLocation *ui;
};

#endif // VIEWLISTOFFRELOCATION_H
