#ifndef VIEWMYPROFILE_H
#define VIEWMYPROFILE_H

#include <QDialog>

namespace Ui {
class ViewMyProfile;
}

class ViewMyProfile : public QDialog
{
    Q_OBJECT

public:
    explicit ViewMyProfile(QWidget *parent = 0);
    ~ViewMyProfile();

private:
    Ui::ViewMyProfile *ui;
};

#endif // VIEWMYPROFILE_H
