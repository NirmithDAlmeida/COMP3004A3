#ifndef CONTROL_SYSTEMS_H
#define CONTROL_SYSTEMS_H

#include <vector>
#include <string>

#include <QTextEdit>
#include <QLineEdit>
#include <QTextStream>
#include <iostream>
#include "Elevator.h"
#include "DisplayWindow.h"
#include "Passenger.h"
#include "ElevatorButton.h"
#include <sstream>

#include <QRandomGenerator>
#include <QTextEdit>

class Control_Systems{
private:
    int CountPass;
    int CountCars;
    int CountFloors;
    bool fire;
    bool overload;
    bool power;
    int safeFloor;
    bool elevatorStuck;
    std::vector<Elevator*> elevators;
    // for passengers going up
    std::vector<passenger*> passengersUp;
    // for passengers going down
    std::vector<passenger*> passengersDown;
    bool ElevatorCalled;//check if elevator is called or not
    bool sensorObstacle;
    int passengerCounter=0;

public:
// not sure on what input will come in here
    Control_Systems(int=3,int=1);
    ~Control_Systems();
    void PopulatePassengers_up(int,QTextEdit *);
    void PopulatePassengers_down(int,QTextEdit *);
    void basicCase();
    void helpButton();
    void DoorObstacle(QTextEdit *);
    void FireCase(QTextEdit *,QLineEdit *);
    void overloadCase(QTextEdit *);
    void outage(QTextEdit *,QLineEdit *);
    bool getElevatorCalled();//might not be necessary
    bool setElevatorCalled();//might not be necessary unless it is to call a available elevator
    void printSafetyFeatures();//this will be the main display showing any safetyIssues - WILL BE CALLED WHEN SAFETY FEATURE IS TRIGGERED
    void printNormalUpdates();//WILL BE CALLED WHEN TEST CASE IS SUCCESSFUL

protected:
    bool hasElevatorArrived();
    bool ElevatorAvailable(Elevator*);
    bool isElevatorStuck(Elevator*);
};

#endif // CONTROL_SYSTEMS_H
