#ifndef VIEWLISTOFFRELOCATION_H
#define VIEWLISTOFFRELOCATION_H

#include <QDialog>

namespace Ui {
class ViewListOffreLocation;
}

/**
 * @brief The ViewListOffreLocation class
 */
class ViewListOffreLocation : public QDialog
{
    Q_OBJECT

    /**
     * @brief The Cols enum
     */
    enum Cols {
        REF = 0,
        DATE_DEBUT = 1,
        DATE_FIN = 2,
        LIEU_DEBUT = 3,
        LIEU_FIN = 4,
        PRIX = 5
    };

public:
    /**
     * @brief ViewListOffreLocation
     * @param parent
     */
    explicit ViewListOffreLocation(QWidget *parent = 0);
    ~ViewListOffreLocation();

    /**
     * @brief RefreshList
     */
    void RefreshList();

private:
    Ui::ViewListOffreLocation *ui;
};

#endif // VIEWLISTOFFRELOCATION_H
