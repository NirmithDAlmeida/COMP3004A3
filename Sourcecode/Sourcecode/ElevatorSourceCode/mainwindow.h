#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

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

private:
    Ui::MainWindow *ui;
    Control_Systems *c;
};
#endif // MAINWINDOW_H