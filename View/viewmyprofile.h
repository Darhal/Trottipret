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

    void SetAvatarPicture(QPixmap& img);

    bool VerifyInfo();

    void FinishEdit();
private slots:
    void accept();

private:
    Ui::ViewMyProfile *ui;
    QString m_AvatarPath;
};

#endif // VIEWMYPROFILE_H
