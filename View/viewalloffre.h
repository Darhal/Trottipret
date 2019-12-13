#ifndef VIEWALLOFFRE_H
#define VIEWALLOFFRE_H

#include <QDialog>

namespace Ui {
class ViewAllOffre;
}

class ViewAllOffre : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAllOffre(QWidget *parent = 0);
    ~ViewAllOffre();

private:
    Ui::ViewAllOffre *ui;
};

#endif // VIEWALLOFFRE_H
