#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "View/viewoffrelocation.h"
#include "View/viewinscription.h"
#include "View/viewconnection.h"
#include <QSignalMapper>
#include <QDebug>
#include <QCloseEvent>
#include "Core/applicationmanager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ApplicationManager::GetInstance(); // intilize the application manager
    // manager.StartApplication();
    ui->setupUi(this); // Initialise le UI

    signalMapper  = new QSignalMapper{ this }; // Allocation dynamique de mon signal mapper
                                               // Ceci doit être alloué dynamiquement
                                               // sinon rien ne fonctionnera

    // Attache nos buttons à la map on event clicked()
    connect(ui->InscriptionButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ConnectionButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->OffreLocationButton, SIGNAL(clicked()), signalMapper, SLOT(map()));

     // Initialise nos buttons avec leur attribus.
    signalMapper->setMapping(ui->InscriptionButton, DialogWindow::SIGNUP);
    signalMapper->setMapping(ui->ConnectionButton, DialogWindow::LOGIN);
    signalMapper->setMapping(ui->OffreLocationButton, DialogWindow::OFFRE_LOCATION);

    // Connecte notre signalMap.
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(OpenDialogWindow(int)));
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Trottipret",
                                                                tr("Are you sure you want to quit the application ?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        ApplicationManager::Free();
    }
}

void MainWindow::OpenDialogWindow(int dialog_id)
{
    // On utilise les avantages de l'heritage ici pour eviter la duplication du code
    QDialog* dialog_wnd = NULL;

    switch(dialog_id) // switch qui decide le type de la fenêtre en fonction de l'argument
    {
    case DialogWindow::SIGNUP:
        dialog_wnd = new ViewInscription(this);
        break;
    case DialogWindow::LOGIN:
        dialog_wnd = new ViewConnection(this);
        break;
    case DialogWindow::OFFRE_LOCATION:
        dialog_wnd = new ViewOffreLocation(this);
        break;
    default:
        return;
    }

    dialog_wnd->setAttribute(Qt::WA_DeleteOnClose); // Il y a pas de free (delete).
                                                    // Cela va liberer la memoire automatiquement
                                                    // à la fermuture
    dialog_wnd->show(); // Affiche notre boîte de dialogue
}

MainWindow::~MainWindow()
{
    // Free de l'UI et le signalMapper
    delete ui;
    delete signalMapper;
}
