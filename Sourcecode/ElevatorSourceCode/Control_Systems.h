#ifndef CONTROL_SYSTEMS_H
#define CONTROL_SYSTEMS_H

#include <vector>
#include <string>

#include "Elevators.h"
#include "DisplayWindow.h"
#include "Passenger.h"
#include "ElevatorButton.h"

class Control_Systems{
private:
    int CountPass;
    int CountCars;
    bool fire;
    bool overload;
    bool power;
    bool elevatorStuck;
    std::vector<Elevator*> elevators;
    std::vector<passenger*> passengers;
    bool ElevatorCalled;//check if elevator is called or not

public:
// not sure on what input will come in here
    Control_Systems();
    ~Control_Systems();
    void basicCase();
    void helpButton();
    void DoorObstacle();
    void FireCase();
    void overloadCase();
    void outage();
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
