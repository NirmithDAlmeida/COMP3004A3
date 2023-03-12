#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include "Control_Systems.h"
#include "Elevator.h"
#include "DisplayWindow.h"
#include "Passenger.h"
#include "ElevatorButton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_StartSimulation_clicked();

    void on_fireSafety_clicked();

    void on_powerOutage_clicked();

    void on_overload_clicked();

    void on_doorObstacle_clicked();

    void populatePassengers();
    void populatePassengers_goingDown();

    void on_MainUseCase_clicked();

    void on_pushButton_4_clicked();

    void on_MainUseCase_2_clicked();

    void on_Down_2_clicked();

private:
    Ui::MainWindow *ui;
    Control_Systems *c;
};
#endif // MAINWINDOW_H
