#ifndef VIEWOFFRELOCATION_H
#define VIEWOFFRELOCATION_H

#include <QDialog>

namespace Ui {
class ViewOffreLocation;
}

class ViewOffreLocation : public QDialog
{
    Q_OBJECT

public:
    explicit ViewOffreLocation(QWidget *parent = nullptr);
    ~ViewOffreLocation();

private:
    Ui::ViewOffreLocation *ui;
};

#endif // VIEWOFFRELOCATION_H
