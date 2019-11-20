#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "View/viewoffrelocation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto v = new ViewOffreLocation(this);
    v->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
