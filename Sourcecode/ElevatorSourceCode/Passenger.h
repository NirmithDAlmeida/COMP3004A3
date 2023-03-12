#ifndef PASSENGER_H
#define PASSENGER_H
#include <iostream>
#include <string>
#include <vector>
#include "ElevatorButton.h"
#include "Door.h"
class passenger{
private:
    int floor;
    std::string name;
    int destFloor;
    float weight=0.0;
    bool isAssigned;
public:
    passenger(std::string,int,float=50);
    passenger(std::string,int,int,float=50);
    ~passenger();
    std::string getName();
    int getFloor();
    float getWeight();
    void setFloor(int);
    void setWeight(float);
    int getDestFloor();//get the first destination floor the passenger goes to
    void setDestFloor(int);
    void requestFloor(int);
    //set passenger to assigned to an elevator or not
    bool getStatus();
    void setStatus(bool);
};

#endif // PASSENGER_H
