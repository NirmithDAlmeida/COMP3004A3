#include<Control_Systems.h>

Control_Systems::Control_Systems(int nFloor=3,int nCar=1){
    CountCars=nCar;
    CountFloors=nFloor;
    fire=false;
    overload=false;
    power=false;
    elevatorStuck=false;
}
Control_Systems::~Control_Systems(){

}

//safety features
//fire
void Control_Systems::FireCase(QTextEdit *t){
    //set fire to true
    fire = true;
    //iterate over all elevator
    //set each elevator to a random floor within the constraint with random amount of passengers
    //send each elevator to safe floor which is 0
    //display every thing onto the main screen
    t->append("Cars"+QString::number(CountCars)+"Floors"+QString::number(CountFloors));
}
//help
//door obstacle
//overload
//power outage
