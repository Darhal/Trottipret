#ifndef VIEWADDTROTTINETTE_H
#define VIEWADDTROTTINETTE_H

#include <QDialog>
#include <QString>

namespace Ui {
class ViewAddTrottinette;
}


/**
 * @brief The ViewAddTrottinette class used to show the window for adding trottinette
 */
class ViewAddTrottinette : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ViewAddTrottinette ctor
     * @param parent
     */
    explicit ViewAddTrottinette(QWidget *parent = 0);

    /**
     * brief ViewAddTrottinette dtor
     */
    ~ViewAddTrottinette();


    /**
     * @brief VerifyData
     * @return bool if data is correct or not
     */
    bool VerifyData();

    /**
     * @brief SubmitData submit and sends the data
     */
    void SubmitData();

private slots:
    void accept() override; // les slots, on surcharge la fonction accept pour ne pas
                            // supprimer la fenêtre lorsque les
                            // informations ne sont pas bonnes

private:
    Ui::ViewAddTrottinette *ui;
    QString m_ImageFilePath; // field used for the image of the trotti
};

#endif // VIEWADDTROTTINETTE_H
