#include "Elevator.h"

Elevator::Elevator(int floor,int nPassenger, float weightLimit){
    floorNumber=floor;
    CountPass=nPassenger;
    WeightLimit=weightLimit;
    overload=false;
    fire=false;
    power=true;
    helpbutton=false;
    elevatorStuck=false;
    sensorObstacle=false;
    isMoving=false;
    isStoppedatFloor=false;
    ReachedDestination=false;
    status=false;

}

Elevator::~Elevator(){}

void Elevator::removeDestFloor(){
    if(destFloor.size()>0){
        destFloor.erase(destFloor.begin());
    }
}

void Elevator::AddToDestFloor(int dest){
    destFloor.push_back(dest);
}

int Elevator::move(int floor){
    floorNumber=floor;
    return floorNumber;
}
void Elevator::setDoor(bool a){
    door->setDoor(a);
}

bool Elevator::getDoorStatus(){
    return door->getDoorOpen();
}
int Elevator::getWeightLimit(){
    return WeightLimit;
}

//GETTERS AND SETTERS
int Elevator::getMaxWeightLimit(){
    return WeightLimit;
}
int Elevator::getFloorNumber(){
    return floorNumber;
}
bool Elevator::getMoving(){
    return isMoving;
}
bool Elevator::getStopped(){
    return isStoppedatFloor;
}
bool Elevator::getStatus(){
    return status;
}
bool Elevator::getReachedDestination(){
    return ReachedDestination;
}
void Elevator::setMoving(){
    isMoving=!isMoving;
}
void Elevator::setStopped(){
    if(isStoppedatFloor){
        isStoppedatFloor=false;
    }else{
        isStoppedatFloor=true;
    }
}
// when user reaches destination
void Elevator::setReachedDestination(){
    if(ReachedDestination){
        ReachedDestination=false;
    }else{
        ReachedDestination=true;
    }
}
void Elevator::setStatus(){
    if(status){
        status=false;
    }else{
        status=true;
    }
}
//safety featrures
bool Elevator::getOverload(){
    return overload;
}
bool Elevator::getFire(){
    return fire;
}
bool Elevator::getSensorInterrupt(){
    return sensorObstacle;
}
//if there is power true no power = false
bool Elevator::getPower(){
    return power;
}
//if button is pressed or not
bool Elevator::getHelpButton(){
    return helpbutton;
}
//if elevator is stuck in between
bool Elevator::getElevatorStuck(){
    return elevatorStuck;
}
void Elevator::setOverload(){
    if(overload){
        overload=false;
    }else{
        overload=true;
    }
}
void Elevator::setFire(){
    fire=!fire;
}
void Elevator::setSensorInterrupt(){
    if(sensorObstacle){
        sensorObstacle=false;
    }else{
        sensorObstacle=true;
    }
}
void Elevator::setPower(){
    if(power){
        power=false;
    }else{
        power=true;
    }
}
void Elevator::setHelpButton(){
    if(helpbutton){
        helpbutton=false;
    }else{
        helpbutton=true;
    }
}
void Elevator::setElevatorStuck(){
    if(elevatorStuck){
        elevatorStuck=false;
    }else{
        elevatorStuck=true;
    }
}

float Elevator::getCurLimit(){
    return currWeightLimit;
}
void Elevator::setCurLimit(float a){
    currWeightLimit=currWeightLimit+a;
}

std::vector<int> Elevator::getDestFloor(){
    return destFloor;
}
