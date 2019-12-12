#ifndef VIEWLISTOFFRELOCATION_H
#define VIEWLISTOFFRELOCATION_H

#include <QDialog>

namespace Ui {
class ViewListOffreLocation;
}

class ViewListOffreLocation : public QDialog
{
    Q_OBJECT

public:
    explicit ViewListOffreLocation(QWidget *parent = 0);
    ~ViewListOffreLocation();

private:
    Ui::ViewListOffreLocation *ui;
};

#endif // VIEWLISTOFFRELOCATION_H
