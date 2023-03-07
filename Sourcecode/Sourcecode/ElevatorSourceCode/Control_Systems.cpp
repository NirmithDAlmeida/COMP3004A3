#include<Control_Systems.h>

Control_Systems::Control_Systems(int nFloor,int nCar){
    CountCars=nCar;
    CountFloors=nFloor;
    fire=false;
    safeFloor=0;
    overload=false;
    power=false;
    elevatorStuck=false;
    //initialize the elevators
    for(int i=1;i<=CountCars;i++){
        Elevator *e=new Elevator(1,0,200);
        elevators.push_back(e);
    }
}
Control_Systems::~Control_Systems(){

}

//safety features
//fire
void Control_Systems::FireCase(QTextEdit *t){
    //set fire to true
    fire = true;
    //populate passengers and each passengers in elevator will need to depart
    //iterate over all elevator
    //set each elevator to a random floor within the constraint with random amount of passengers
    //send each elevator to safe floor which is 0
    //display every thing onto the main screen
    t->append("HOUSE/BLDG FIRE ALARM TRIGGERED\n");
    for(int i=0;i<CountCars;i++){
        //t->append("Cars# "+QString::number(i));
        t->append("Cars# "+QString::number(i+1)+"\n");
        elevators[i]->setFire();
        if(elevators[i]->getFire()){
            t->append("Fire is there and we are moving to the safe floor");
        }
        elevators[i]->move(safeFloor);
        t->append("Cars#" +QString::number(i+1)+"is now at safe floor# "+QString::number(safeFloor)+"\n");
        //reset to default settings
        elevators[i]->setFire();
    }
    fire=false;
}
//help
//door obstacle
//overload
//power outage
void Control_Systems::outage(QTextEdit *t){
    power=true;
    //populate passengers and each passengers in elevator will need to depart
    t->append("HOUSE/BLDG POWER OUTAGE ALARM TRIGGERED\n");
    for(int i=0;i<CountCars;i++){
        //t->append("Cars# "+QString::number(i));
        t->append("Cars# "+QString::number(i+1)+"\n");
        elevators[i]->setPower();
        if(elevators[i]->getPower()){
            t->append("Power is not there and we are moving to the safe floor");
        }
        elevators[i]->move(safeFloor);
        t->append("Cars#" +QString::number(i+1)+"is now at safe floor# "+QString::number(safeFloor)+"\n");
        //reset to default settings
        elevators[i]->setPower();
    }
    power=false;
}
