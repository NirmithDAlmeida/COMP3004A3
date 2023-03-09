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
    std::string Name;
    std::vector<int> destFloor;
    float weight=0.0;
public:
    passenger(std::string,int,float);
    ~passenger();
    bool getFloor();
    bool getWeight();
    bool setFloor(int);
    bool setWeight(float);
    int getDestFloor();//get the first destination floor the passenger goes to
    void setDestFloor(int);
    void requestFloor(int);
};

#endif // PASSENGER_H
