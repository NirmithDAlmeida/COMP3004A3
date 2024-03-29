#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <vector>
#include<iostream>
#include <string>
#include "Door.h"
#include "DisplayWindow.h"
class Elevator{
private:
    Door *door = new Door();
    int floorNumber;
    int CountPass;
    float currWeightLimit=0;
    float WeightLimit;// might change to MaxPassengers
    std::vector<int> destFloor;
    //safety feature
    bool overload;
    bool fire;
    bool power;
    bool helpbutton;
    bool elevatorStuck;
    bool sensorObstacle;
    //general behaviour
    bool isMoving;// can be replaced with Elevator Stuck - issue will be when elevator is stopped
    bool isStoppedatFloor;//Fix above issue
    bool ReachedDestination;//will be false when elevator is moving will be true when elevator is stopped at THE FINAL FLOOR in the destFloor vector
    bool status;//to see if the elevator is occupied and busy or it is idle- idle only WHEN PASSENGER COUNT is 0 through counter

public:
    Elevator(int=1,int=0,float=200);
    ~Elevator();
    //main functions
    int move(int);
    void setDoor(bool);
    int getWeightLimit();
    bool getDoorStatus();
    void removeDestFloor();
    //printer statements
    //void printElevatorFloor(int);
    //void printSafetyMessages(string);
    //getters and setters
    //general behaviour
    int getMaxWeightLimit();
    int getFloorNumber();
    bool getMoving();
    bool getStopped();
    bool getStatus();
    bool getReachedDestination();
    std::vector<int> getDestFloor();
    void AddToDestFloor(int);
    void setMoving();
    void setStopped();
    void setReachedDestination();// when user reaches destination
    void setStatus();
    //safety featrures
    bool getOverload();
    bool getFire();
    bool getSensorInterrupt();
    bool getPower();//if there is power true no power = false
    bool getHelpButton();//if button is pressed or not
    bool getElevatorStuck();//if elevator is stuck in between
    float getCurLimit();
    void setOverload();
    void setFire();
    void setSensorInterrupt();
    void setPower();
    void setHelpButton(bool);
    void setElevatorStuck();
    void setCurLimit(float);
};

#endif // ELEVATOR_H
