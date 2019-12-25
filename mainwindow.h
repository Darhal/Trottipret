#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QCloseEvent;

/**
 * @class MainWindow
 * @brief Classe MainWIndow qui possède l'interface utilisateur de la fenêtre principale
 * et hérite de QMainWindow
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @enum Enum à utiliser plus tard pour résumer une fonction
     * qui ouvrira des boîtes de dialogue
    */
    enum DialogWindow
    {
        LOGIN = 0x0,
        SIGNUP = 0x1,
        VIEW_OFFRE_LOCATION = 0x2,
        VIEW_LISTE_TROTTI = 0x3,
        VIEW_ALL_OFFRE = 0x4,
        VIEW_ACTIVE_LOCATIONS = 0x5,
        VIEW_PROFILE = 0x6,
    };

    /**
     * @fn Constructeur de la fenêtre principale
     * @param  QWidget* parent
     * @return rien
    */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Destructeur de la fenêtre principale
    */
    ~MainWindow();

    /**
     * @brief Fonction utile pour recuperer les elements d'UI de la fenetre principale
     * par les autres classes pour faciliter ses modifications.
     * @param  QWidget* parent
     * @return rien
    */
    Ui::MainWindow* GetUI() {return ui;}

    void closeEvent(QCloseEvent* event) override;

    void ToggleButtons(bool b);

private slots:
    /**
     * @brief Fonction pour ouvrir les boîtes de dialogue
     * @param  QWidget* parent
     * @return rien
    */
    void OpenDialogWindow(int dialog_id);

private:
    Ui::MainWindow *ui; // Libéré sur appel de MainWindow Destructor
    class QSignalMapper* signalMapper; // Un mappeur de signal à utiliser ultérieurement
                                       // pour résumer la duplication de code.
                                       // Libéré sur appel de MainWindow Destructor
};

#endif // MAINWINDOW_H
