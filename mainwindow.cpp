#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "View/viewoffrelocation.h"
#include "View/viewinscription.h"
#include "View/viewconnection.h"
#include "View/viewalloffre.h"
#include "View/viewlistoffrelocation.h"
#include <QSignalMapper>
#include <QDebug>
#include <QCloseEvent>
#include "Core/applicationmanager.h"
#include <QMessageBox>
#include <View/viewlistetrottinette.h>
#include <View/viewlocations.h>
#include <View/viewmyprofile.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ApplicationManager::GetInstance(); // intilize the application manager
    // manager.StartApplication();
    ui->setupUi(this); // Initialise le UI

    ToggleButtons(false); // Disable all buttons when logout
    signalMapper  = new QSignalMapper{ this }; // Allocation dynamique de mon signal mapper
                                               // Ceci doit être alloué dynamiquement
                                               // sinon rien ne fonctionnera

    // Attache nos buttons à la map on event clicked()
    connect(ui->InscriptionButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ConnectionButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ListOffreLocButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ListeTrottiButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->AllOffreButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ActiveLocationButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->MyProfile, SIGNAL(clicked()), signalMapper, SLOT(map()));

     // Initialise nos buttons avec leur attribus.
    signalMapper->setMapping(ui->InscriptionButton, DialogWindow::SIGNUP);
    signalMapper->setMapping(ui->ConnectionButton, DialogWindow::LOGIN);
    signalMapper->setMapping(ui->ListOffreLocButton, DialogWindow::VIEW_OFFRE_LOCATION);
    signalMapper->setMapping(ui->ListeTrottiButton, DialogWindow::VIEW_LISTE_TROTTI);
    signalMapper->setMapping(ui->AllOffreButton, DialogWindow::VIEW_ALL_OFFRE);
    signalMapper->setMapping(ui->ActiveLocationButton, DialogWindow::VIEW_ACTIVE_LOCATIONS);
    signalMapper->setMapping(ui->MyProfile, DialogWindow::VIEW_PROFILE);

    // Connecte notre signalMap.
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(OpenDialogWindow(int)));

    connect(ui->LogOut, &QPushButton::clicked, this, [this](){
        ApplicationManager::GetInstance().SetCurrentUser(nullptr);
        ui->connected_user->setStyleSheet("color: red;");
        ui->connected_user->setText("Utilisateur Anonyme, vous n'êtes pas connecté.");
        this->ToggleButtons(false);
    });
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Trottipret",
                                                                tr("Etes-vous sûr de vouloir quitter l'application ?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
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
    case DialogWindow::VIEW_OFFRE_LOCATION:
        dialog_wnd = new ViewListOffreLocation(this);
        break;
    case DialogWindow::VIEW_LISTE_TROTTI:
        dialog_wnd = new ViewListeTrottinette(this);
        break;
    case DialogWindow::VIEW_ALL_OFFRE:
        dialog_wnd = new ViewAllOffre(this);
        break;
    case DialogWindow::VIEW_ACTIVE_LOCATIONS:
        dialog_wnd = new ViewLocations(this);
        break;
    case DialogWindow::VIEW_PROFILE:
        dialog_wnd = new ViewMyProfile(this);
        break;
    default:
        return;
    }

    if (dialog_wnd){
        dialog_wnd->setAttribute(Qt::WA_DeleteOnClose); // Il y a pas de free (delete).
                                                        // Cela va liberer la memoire automatiquement
                                                        // à la fermuture
        dialog_wnd->show(); // Affiche notre boîte de dialogue
    }
}

void MainWindow::ToggleButtons(bool b)
{
    if (b){

    }else{
        QPixmap img_pixmap = QPixmap(":/Resources/Images/trotinette.png");
        ui->imageTrotti->setPixmap(img_pixmap);
        ui->imageTrotti->setScaledContents( true );
        ui->imageTrotti->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }


    ui->ListOffreLocButton->setEnabled(b);
    ui->ListeTrottiButton->setEnabled(b);
    ui->ActiveLocationButton->setEnabled(b);
    ui->MyProfile->setEnabled(b);
    ui->LogOut->setEnabled(b);

    ui->ConnectionButton->setEnabled(!b);
    ui->InscriptionButton->setEnabled(!b);
}

MainWindow::~MainWindow()
{
    // Free de l'UI et le signalMapper
    delete ui;
    delete signalMapper;
}
