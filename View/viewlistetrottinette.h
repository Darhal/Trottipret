#ifndef VIEWLISTETROTTINETTE_H
#define VIEWLISTETROTTINETTE_H

#include <QDialog>

namespace Ui {
class ViewListeTrottinette;
}

/**
 * @brief The ViewListeTrottinette class reponsible for managment of trottienttes
 */
class ViewListeTrottinette : public QDialog
{
    Q_OBJECT

    /**
     * @brief The Cols enum colums ids
     */
    enum Cols {
        REF = 0,
        MODEL = 1,
        ETAT = 2,
    };
public:
    /**
     * @brief ViewListeTrottinette
     * @param parent
     */
    explicit ViewListeTrottinette(QWidget *parent = 0);

    /**
     * @brief ~ViewListeTrottinette
     */
    ~ViewListeTrottinette();

    /**
     * @brief RefreshList
     */
    void RefreshList();
private slots:
    /**
     * @brief OnRowSelection on row selection event
     */
    void OnRowSelection();
private:
    Ui::ViewListeTrottinette *ui;
};

#endif // VIEWLISTETROTTINETTE_H
