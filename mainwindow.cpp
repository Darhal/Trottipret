#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "View/viewoffrelocation.h"
#include "View/viewinscription.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->InscriptionButton, SIGNAL(clicked()), SLOT(OpenInscriptionWindow()));
}

void MainWindow::OpenInscriptionWindow()
{
    ViewInscription* inscription_wnd = new ViewInscription(this);
    inscription_wnd->setAttribute(Qt::WA_DeleteOnClose);
    inscription_wnd->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
