#ifndef VIEWLISTETROTTINETTE_H
#define VIEWLISTETROTTINETTE_H

#include <QDialog>

namespace Ui {
class ViewListeTrottinette;
}

class ViewListeTrottinette : public QDialog
{
    Q_OBJECT

public:
    explicit ViewListeTrottinette(QWidget *parent = 0);
    ~ViewListeTrottinette();

private slots:
    void OnRowSelection();
private:
    Ui::ViewListeTrottinette *ui;
};

#endif // VIEWLISTETROTTINETTE_H
