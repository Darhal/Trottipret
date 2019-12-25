#ifndef VIEWLOCATIONS_H
#define VIEWLOCATIONS_H

#include <QDialog>

namespace Ui {
class ViewLocations;
}

/**
 * @brief The ViewLocations class
 */
class ViewLocations : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ViewLocations
     * @param parent
     */
    explicit ViewLocations(QWidget *parent = 0);
    ~ViewLocations();

    /**
     * @brief RefreshList
     */
    void RefreshList();
private:
    Ui::ViewLocations *ui;
};

#endif // VIEWLOCATIONS_H
