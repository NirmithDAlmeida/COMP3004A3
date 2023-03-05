#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString nFloor = ui->numberFloor->text();
    QString nCar = ui->numberCar->text();
    //we do it  for one system now
    c = new Control_Systems(3,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_StartSimulation_clicked()
{
    ui->OutputBox->append("this button is activated and simulation is started");
    ui->StartSimulation->setVisible(false);
    ui->numberFloor->setReadOnly(true);
    ui->numberCar->setReadOnly(true);
}

void MainWindow::on_fireSafety_clicked()
{
    //clear previous text history
    ui->OutputBox->clear();
    ui->OutputBox->append("Fire button safety is activated \n");
    c->FireCase(ui->OutputBox);
    ui->OutputBox->append("/n =========== Fire Safety tested =========== \n");
}