#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "View/viewoffrelocation.h"
#include "View/viewinscription.h"
#include "View/viewconnection.h"
#include <QSignalMapper>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    signalMapper  = new QSignalMapper{ this }; // liberation dans le destructeur
    connect(ui->InscriptionButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ConnectionButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->OffreLocationButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->InscriptionButton, DialogWindow::SIGNUP);
    signalMapper->setMapping(ui->ConnectionButton, DialogWindow::LOGIN);
    signalMapper->setMapping(ui->OffreLocationButton, DialogWindow::OFFRE_LOCATION);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(OpenDialogWindow(int)));
}

void MainWindow::OpenDialogWindow(int dialog_id)
{
    QDialog* dialog_wnd = NULL;

    switch(dialog_id)
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

    dialog_wnd->setAttribute(Qt::WA_DeleteOnClose); // Libere la memoire automatiquement a la fermuture
    dialog_wnd->show();
}



MainWindow::~MainWindow()
{
    delete ui;
    delete signalMapper;
}
