#include<Control_Systems.h>

Control_Systems::Control_Systems(int nFloor,int nCar){
    CountCars=nCar;
    CountFloors=nFloor;
    fire=false;
    safeFloor=0;
    overload=false;
    power=false;
    elevatorStuck=false;
    sensorObstacle=false;
    //initialize the elevators
    for(int i=1;i<=CountCars;i++){
        Elevator *e=new Elevator(1,0,200);
        elevators.push_back(e);
        e->setDoor(false);
    }
}
Control_Systems::~Control_Systems(){
    for(size_t i=0;i<elevators.size();i++){
        delete elevators[i];
    }
}

//safety features
//fire
void Control_Systems::FireCase(QTextEdit *t,QLineEdit *y){
    //set fire to true
    fire = true;
    y->setText(QString::number(200)+" kg");
    //populate passengers and each passengers in elevator will need to depart
    //iterate over all elevator
    //set each elevator to a random floor within the constraint with random amount of passengers
    //send each elevator to safe floor which is 0
    //display every thing onto the main screen
    t->append("HOUSE/BLDG FIRE ALARM TRIGGERED\n");
    for(size_t i=0;i<elevators.size();i++){
        //t->append("Cars# "+QString::number(i));
        t->append("Cars# "+QString::number(i+1)+"\n");
        elevators[i]->setFire();
        if(elevators[i]->getFire()){
            t->append("Fire is there and we are moving to the safe floor");

        }
        elevators[i]->move(safeFloor);
        t->append("Cars#" +QString::number(i+1)+"is now at safe floor# "+QString::number(safeFloor)+"\n");
        t->append("\nDOOR OPENING\n");
        elevators[i]->setDoor(true);
        //check if passengers are there
            //if yes iterate over each passenger and kick each one out
            //if not break out of loop
        //populate passengers and each passengers in elevator will need to depart
        t->append("\nDOOR CLOSING\n");
        elevators[i]->setDoor(false);
        //reset to default settings
        elevators[i]->setFire();
    }
    fire=false;
}
//help
//door obstacle
//overload
//power outage
void Control_Systems::outage(QTextEdit *t,QLineEdit *y){
    power=true;
    y->setText(QString::number(200)+" kg");
    //populate passengers and each passengers in elevator will need to depart
    t->append("HOUSE/BLDG POWER OUTAGE ALARM TRIGGERED\n");
    for(size_t i=0;i<elevators.size();i++){
        //t->append("Cars# "+QString::number(i));
        t->append("Cars# "+QString::number(i+1)+"\n");
        elevators[i]->setPower();
        if(elevators[i]->getPower()){
            t->append("Power is not there and we are moving to the safe floor");
        }
        elevators[i]->move(safeFloor);
        t->append("Cars#" +QString::number(i+1)+"is now at safe floor# "+QString::number(safeFloor)+"\n");
        t->append("\nDOOR OPENING\n");
        elevators[i]->setDoor(true);
        //check if passengers are there
            //if yes iterate over each passenger and kick each one out
            //if not break out of loop
        t->append("\nDOOR CLOSING\n");
        elevators[i]->setDoor(false);
        //reset to default settings
        elevators[i]->setPower();
    }
    power=false;
}

void Control_Systems::overloadCase(QTextEdit *y){
    overload=true;
    int broken_weightLimit=230;
    y->append("ELEVATOR OVERLOAD ALARM TRIGGERED\n");
    //Get random elevator within 1 and nCars
    int randomElevator=QRandomGenerator::global()->bounded(1,CountCars);
    y->append("Elevator #"+QString::number(randomElevator));
    elevators[randomElevator]->setDoor(true);
    y->append("WEIGHT LIMIT EXCEEDED - "+QString::number(broken_weightLimit)+"/nexpected Weight Limit - "+QString::number(elevators[randomElevator]->getWeightLimit()));
    y-> append("\n Please loose weight \n");
    if(elevators[randomElevator]->getDoorStatus()){
        y->append("\nDOOR IS OPEN AND WILL REMAIN OPEN TILL WEIGHT IS REDUCED\n");
        y->append("Passenger leaves");
        //generate random number from passenger list and kick one person out
        y->append("\n Door closes\n");
        elevators[randomElevator]->setDoor(false);
    }
    overload=false;
}

void Control_Systems::DoorObstacle(QTextEdit *y){
    sensorObstacle=true;
    y->append("DOOR SENSORS TRIGGERED\n");
    //Get random elevator within 1 and nCars
    int randomElevator=QRandomGenerator::global()->bounded(1,CountCars);
    y->append("Elevator #"+QString::number(randomElevator));
    elevators[randomElevator]->setDoor(true);
    elevators[randomElevator]->setSensorInterrupt();
    y-> append("\n PLEASE REMOVE THE OBSTACLE \n");
    y-> append("\nDoor Sensor is still triggered \n");

    if(elevators[randomElevator]->getDoorStatus()){
        y->append("\nDOOR IS OPEN AND WILL REMAIN OPEN TILL OBSTACLE IS REMOVED\n");
        y->append("Passenger removes obstacle");
        y->append("\n Door closes\n");
        elevators[randomElevator]->setDoor(false);
        elevators[randomElevator]->setSensorInterrupt();
    }
    sensorObstacle=false;
}
