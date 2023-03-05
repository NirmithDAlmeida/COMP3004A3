#ifndef PASSENGER_H
#define PASSENGER_H

#include "ElevatorButton.h"

class passenger{
private:
    int floor;
    string Name;
    vector<int> destFloor;
    float weight=0.0;
public:
    passenger(string,int,float);
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
