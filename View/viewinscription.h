#ifndef VIEWINSCRIPTION_H
#define VIEWINSCRIPTION_H

#include <QDialog>

namespace Ui {
class ViewInscription;
}

class ViewInscription : public QDialog
{
    Q_OBJECT

public:
    explicit ViewInscription(QWidget *parent = 0);
    ~ViewInscription();

private:
    Ui::ViewInscription *ui;
};

#endif // VIEWINSCRIPTION_H
