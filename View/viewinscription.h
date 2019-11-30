#ifndef VIEWINSCRIPTION_H
#define VIEWINSCRIPTION_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class ViewInscription;
}

class ViewInscription : public QDialog
{
    Q_OBJECT

public:
    explicit ViewInscription(QWidget *parent = 0);
    ~ViewInscription();
    bool VerifySignupInformations();

private slots:
    void on_buttonBox_accepted();
    void accept() override;

private:
    Ui::ViewInscription *ui;
};

#endif // VIEWINSCRIPTION_H
