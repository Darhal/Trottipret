#ifndef VIEWLISTETROTTINETTE_H
#define VIEWLISTETROTTINETTE_H

#include <QDialog>

namespace Ui {
class ViewListeTrottinette;
}

class ViewListeTrottinette : public QDialog
{
    Q_OBJECT

    enum Cols {
        REF = 0,
        MODEL = 1,
        ETAT = 2,
    };
public:
    explicit ViewListeTrottinette(QWidget *parent = 0);
    ~ViewListeTrottinette();

private slots:
    void OnRowSelection();
private:
    Ui::ViewListeTrottinette *ui;
};

#endif // VIEWLISTETROTTINETTE_H
