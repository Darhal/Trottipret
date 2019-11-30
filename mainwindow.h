#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

/*
 * Classe MainWIndow qui possède l'interface utilisateur de la fenêtre principale
 * et hérite de QMainWindow
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*
     * Enum à utiliser plus tard pour résumer une fonction
     * qui ouvrira des boîtes de dialogue
    */
    enum DialogWindow
    {
        LOGIN = 0x0,
        SIGNUP = 0x1,
        OFFRE_LOCATION = 0x2,
    };

    // Constructeur de la fenêtre principale
    explicit MainWindow(QWidget *parent = 0);

    // Destructeur de la fenêtre principale
    ~MainWindow();

    // Fonction utile a recuperer les elements d'UI de la fenetre principale
    // par les autres classes pour faciliter ses modifications.
    Ui::MainWindow* GetUI() {return ui;}

private slots:
    // Fonction pour ouvrir les boîtes de dialogue
    void OpenDialogWindow(int dialog_id);

private:
    Ui::MainWindow *ui; // Libéré sur appel de MainWindow Destructor
    class QSignalMapper* signalMapper; // Un mappeur de signal à utiliser ultérieurement
                                       // pour résumer la duplication de code.
                                       // Libéré sur appel de MainWindow Destructor
};

#endif // MAINWINDOW_H
