#ifndef VIEWADDTROTTINETTE_H
#define VIEWADDTROTTINETTE_H

#include <QDialog>
#include <QString>

namespace Ui {
class ViewAddTrottinette;
}

class ViewAddTrottinette : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAddTrottinette(QWidget *parent = 0);
    ~ViewAddTrottinette();

    bool VerifyData();

    void SubmitData();

private slots:
    void accept() override; // les slots, on surcharge la fonction accept pour ne pas
                            // supprimer la fenêtre lorsque les
                            // informations ne sont pas bonnes

private:
    Ui::ViewAddTrottinette *ui;
    QString m_ImageFilePath;
};

#endif // VIEWADDTROTTINETTE_H
