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
    ui->numberFloor->setReadOnly(true);
    ui->numberCar->setReadOnly(true);
    QString nFloor = ui->numberFloor->text();
    QString nCar = ui->numberCar->text();
    //we do it  for one system now
    c = new Control_Systems(nFloor.toInt(),nCar.toInt());
    for(int i=0;i<nFloor.toInt();i++){
        ui->comboBox_3->addItem(QString::number(i));
    }
}

void MainWindow::on_fireSafety_clicked()
{
    //clear previous text history
    ui->OutputBox->clear();
    ui->OutputBox->append("Fire button safety is activated \n");
    c->FireCase(ui->OutputBox,ui->CurrentWeight);
    ui->OutputBox->append("/n =========== Fire Safety tested =========== \n");
    ui->fireSafety->setDisabled(true);
    ui->powerOutage->setDisabled(false);
    ui->overload->setDisabled(false);
    ui->doorObstacle->setDisabled(false);
}

void MainWindow::on_powerOutage_clicked()
{
    //clear previous text history
    ui->overload->setDisabled(false);
    ui->fireSafety->setDisabled(false);
    ui->doorObstacle->setDisabled(false);
    ui->OutputBox->clear();
    ui->OutputBox->append("Power button safety is activated \n");
    c->outage(ui->OutputBox,ui->CurrentWeight);
    ui->OutputBox->append("/n =========== Power Safety tested =========== \n");
    ui->powerOutage->setDisabled(true);
}

void MainWindow::on_overload_clicked()
{
    ui->powerOutage->setDisabled(false);
    ui->fireSafety->setDisabled(false);
    ui->doorObstacle->setDisabled(false);
    //if(ui->powerOutage->g)
    ui->OutputBox->clear();
    ui->OutputBox->append("Overload button safety is activated \n");
    c->overloadCase(ui->OutputBox);
    ui->OutputBox->append("/n =========== Overloaded Safety tested =========== \n");
    ui->overload->setDisabled(true);
}

void MainWindow::on_doorObstacle_clicked()
{
    ui->powerOutage->setDisabled(false);
    ui->fireSafety->setDisabled(false);
    ui->overload->setDisabled(false);
    //if(ui->powerOutage->g)
    ui->OutputBox->clear();
    ui->OutputBox->append("Door Sensor safety is activated \n");
    c->DoorObstacle(ui->OutputBox);
    ui->OutputBox->append("/n =========== Door Sensor Safety tested =========== \n");
    ui->doorObstacle->setDisabled(true);
}
