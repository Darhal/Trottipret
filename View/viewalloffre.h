#ifndef VIEWALLOFFRE_H
#define VIEWALLOFFRE_H

#include <QDialog>

namespace Ui {
class ViewAllOffre;
}


/**
 * @brief The ViewAllOffre class
 * responsilbe to show all the offers submited by the users
 */
class ViewAllOffre : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ViewAllOffre ctor
     * @param parent
     */
    explicit ViewAllOffre(QWidget *parent = 0);

    /**
     * @brief ~ViewAllOffre dtor
     */
    ~ViewAllOffre();

    /**
     * @brief RefreshList refresh the offers list
     */
    void RefreshList();

private:
    Ui::ViewAllOffre *ui;
};

#endif // VIEWALLOFFRE_H
