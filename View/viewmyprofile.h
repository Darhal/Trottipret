#ifndef VIEWMYPROFILE_H
#define VIEWMYPROFILE_H

#include <QDialog>

namespace Ui {
class ViewMyProfile;
}

/**
 * @brief The ViewMyProfile class will handle the UI behind the profile of the user
 */
class ViewMyProfile : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ViewMyProfile
     * @param parent
     */
    explicit ViewMyProfile(QWidget *parent = 0);
    ~ViewMyProfile();

    /**
     * @brief SetAvatarPicture handle changing the avatar picture
     * @param img
     */
    void SetAvatarPicture(QPixmap& img);

    /**
     * @brief VerifyInfo verify all the infos
     * @return
     */
    bool VerifyInfo();

    /**
     * @brief FinishEdit submit the data and update the database
     */
    void FinishEdit();
private slots:
    void accept(); // pressing OK

private:
    Ui::ViewMyProfile *ui;
    QString m_AvatarPath; // avatar path
};

#endif // VIEWMYPROFILE_H
