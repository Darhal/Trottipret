#ifndef VIEWLOCATIONS_H
#define VIEWLOCATIONS_H

#include <QDialog>

namespace Ui {
class ViewLocations;
}

class ViewLocations : public QDialog
{
    Q_OBJECT

public:
    explicit ViewLocations(QWidget *parent = 0);
    ~ViewLocations();

    void RefreshList();
private:
    Ui::ViewLocations *ui;
};

#endif // VIEWLOCATIONS_H
