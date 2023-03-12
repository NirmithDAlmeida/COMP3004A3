#include "Passenger.h"

passenger::passenger(std::string n,int a,float c){
    name=n;
    floor=a;
    weight=c;
    isAssigned=false;
}

passenger::passenger(std::string n,int floor2,int destn2,float c){
    name=n;
    floor=floor2;
    weight=c;
    destFloor=destn2;
    isAssigned=false;
}

passenger::~passenger(){}


std::string passenger::getName(){
    return name;
}

int passenger::getFloor(){
    return floor;
}
bool passenger::getStatus(){
    return isAssigned;
}
void passenger::setStatus(bool a){
    isAssigned=a;
}
float passenger::getWeight(){
    return weight;
}

int passenger::getDestFloor(){
    return destFloor;
}
