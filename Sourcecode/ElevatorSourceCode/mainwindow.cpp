#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_StartSimulation_clicked()
{
    ui->OutputBox->append("this button is activated and simulation is started");
    ui->StartSimulation->setVisible(false);
}
