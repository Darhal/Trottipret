#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum DialogWindow
    {
        LOGIN = 0x0,
        SIGNUP = 0x1,
        OFFRE_LOCATION = 0x2,
    };

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    Ui::MainWindow* GetUI() {return ui;}
private slots:
    void OpenDialogWindow(int dialog_id);

private:
    Ui::MainWindow *ui;
    class QSignalMapper* signalMapper;
};

#endif // MAINWINDOW_H
