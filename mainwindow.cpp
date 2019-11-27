#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "View/viewoffrelocation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // à ajouter lors du clique sur le button "buttonAjouterOffre"
    auto v = new ViewOffreLocation(this);
    v->show();
    v->move(700,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
