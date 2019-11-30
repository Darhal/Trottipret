#ifndef VIEWCONNECTION_H
#define VIEWCONNECTION_H

#include <QDialog>

namespace Ui {
class ViewConnection;
}

class ViewConnection : public QDialog
{
    Q_OBJECT

public:
    explicit ViewConnection(QWidget *parent = 0);

    bool VerifyLoginInformations();

    void FinishLogin();

    ~ViewConnection();

private slots:
    void accept() override;

private:
    Ui::ViewConnection *ui;
};

#endif // VIEWCONNECTION_H
