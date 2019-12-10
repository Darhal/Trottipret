#ifndef VIEWLISTEOFFRE_H
#define VIEWLISTEOFFRE_H

#include <QDialog>

namespace Ui {
class ViewListeOffre;
}

class ViewListeOffre : public QDialog
{
    Q_OBJECT

public:
    explicit ViewListeOffre(QWidget *parent = nullptr);
    ~ViewListeOffre();

private:
    Ui::ViewListeOffre *ui;
};

#endif // VIEWLISTEOFFRE_H
