#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Up,SIGNAL(clicked()),this,SLOT(populatePassengers()));
    connect(ui->Down,SIGNAL(clicked()),this,SLOT(populatePassengers_goingDown()));

    ui->MainUseCase->setDisabled(true);
    ui->MainUseCase_2->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MainUseCase_clicked()
{
    ui->fireSafety->setDisabled(false);
    ui->powerOutage->setDisabled(false);
    ui->overload->setDisabled(false);
    ui->doorObstacle->setDisabled(false);
    ui->OutputBox->clear();
    ui->OutputBox->append("\nMAIN USE CASE 1\n");
    //disable destination since that is only for Use Case 2
    ui->comboBox_4->setDisabled(false);
    c->basicCase(ui->OutputBox);
    ui->MainUseCase_2->setDisabled(false);
    ui->MainUseCase->setDisabled(true);
    //send elevator to floor
    //pick up passenger
    //go in particular direction
    //initial all elevator is at floor 0
    //first scenario assign one elevator till weight limit reached and head to other floors

}

void MainWindow::on_MainUseCase_2_clicked()
{
    //ui->DisplayWindow->clear();
    ui->fireSafety->setDisabled(false);
    ui->powerOutage->setDisabled(false);
    ui->overload->setDisabled(false);
    ui->doorObstacle->setDisabled(false);
    ui->OutputBox->clear();
    //disable destination since that is only for Use Case 2
    ui->comboBox_4->setDisabled(false);
    ui->MainUseCase_2->setDisabled(true);
    ui->MainUseCase->setDisabled(false);
    c->basicCase2(ui->OutputBox);
}

//WE NEED 2 POSSIBLE SELECTIONS
//IF UP button SAME SCENARIO for DOWN
//- dictionary type tp store and save data
//- sort it so all floors go in order
//get floor number
//ui->DisplayWindow->append("WE PRESSED A BTN Floor #"+ui->comboBox_3->currentText());
//reuse passenger data collected here

void MainWindow::populatePassengers(){
    if(ui->comboBox_4->isEnabled()){
        c->PopulatePassengers_up2(ui->comboBox_3->currentText().toInt(),ui->DisplayWindow,ui->comboBox_4->currentText().toInt());
    }
    else{
        c->PopulatePassengers_up(ui->comboBox_3->currentText().toInt(),ui->DisplayWindow);
    }
    ui->MainUseCase->setDisabled(false);
    ui->MainUseCase_2->setDisabled(false);
}
void MainWindow::populatePassengers_goingDown(){
    if(ui->comboBox_4->isEnabled()){
        c->PopulatePassengers_down2(ui->comboBox_3->currentText().toInt(),ui->DisplayWindow,ui->comboBox_4->currentText().toInt());
    }
    else{
        c->PopulatePassengers_down(ui->comboBox_3->currentText().toInt(),ui->DisplayWindow);
     }
    ui->MainUseCase->setDisabled(false);
    ui->MainUseCase_2->setDisabled(false);
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
    for(int i=1;i<=nFloor.toInt();i++){
        ui->comboBox_3->addItem(QString::number(i));
        ui->comboBox_4->addItem(QString::number(i));
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

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_Down_2_clicked()
{
    ui->comboBox_4->setEnabled(false);
    //int a=ui->comboBox_4->isEnabled();
}

void MainWindow::on_Open_clicked()
{
    ui->OutputBox->clear();
    c->DoorScenario(ui->OutputBox,true);
}

void MainWindow::on_Close_clicked()
{
    ui->OutputBox->clear();
    c->DoorScenario(ui->OutputBox,false);
}
