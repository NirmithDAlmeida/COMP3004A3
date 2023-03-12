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
    for(size_t i=0;i<passengersUp.size();i++){
        delete passengersUp[i];
    }
    for(size_t i=0;i<passengersDown.size();i++){
        delete passengersDown[i];
    }
    for(size_t i=0;i<passengersUp2.size();i++){
        delete passengersUp2[i];
    }
    for(size_t i=0;i<passengersDown2.size();i++){
        delete passengersDown2[i];
    }
}
//int passengerCounter=0;
void Control_Systems::PopulatePassengers_up(int floor,QTextEdit *t){
    passengerCounter=passengerCounter+1;
    std::string passengerName="Passenger#"+std::to_string(passengerCounter);
    passenger *p=new passenger(passengerName,floor,50);
    passengersUp.push_back(p);
    t->append(QString::number(passengerCounter)+" Passenger Added from floor# "+QString::number(floor)+" Going UP");
}

void Control_Systems::PopulatePassengers_down(int floor, QTextEdit *t){
    passengerCounter=passengerCounter+1;
    std::string passengerName="Passenger#"+std::to_string(passengerCounter);
    passenger *p=new passenger(passengerName,floor,50);
    passengersDown.push_back(p);
    t->append(QString::number(passengerCounter)+" Passenger Added from floor# "+QString::number(floor)+" Going DOWN");
}

//allocation strategy 1

/*void Control_Systems::assignElevator(QTextEdit *t){

}*/
void Control_Systems::basicCase(QTextEdit *t){
    //if no passenger in list print message cannot allocate due to no passenger - not necessary
    //access passenger classs
    //iterate over each elevator first
    /*std::sort(passengersUp.begin(), passengersUp.end(), [](passenger& lhs,passenger& rhs) {
          return lhs.getFloor() < rhs.getFloor();
       });*/
    /*for(size_t i=0;i<passengersUp.size();i++){
        t->append("Passeger"+QString::fromStdString(passengersUp[i]->getName()));
    }*/
    for(size_t i=0;i<elevators.size();i++){
        int whereElevator=elevators[i]->getFloorNumber();
        //int NPassengerUp=passengersUp.size();
        std::string name="";
        t->append("Elevator# "+QString::number(i+1)+" at Floor# "+QString::number(whereElevator));
        if(passengersDown.size()==0 || passengersUp.size()==0){

            for(size_t i=0;i<passengersUp.size();i++){
                name=passengersUp[i]->getName();
                t->append("Passenger Name"+QString::fromStdString(name)+"Enters Elevator and ");
                //elevators[i]->destFloor.push_back(value)
            }
        }
    }
        //set first default variable where if used for first time all elevators are at ground level i.e. floor - 1
        //if there are no down passengers send an elevator to corresponding floor to pick up passengers
            //go to their destination
        //else if there are no up passengers and only passengers going down
            //go to highest floor to go down and start from there
}

void Control_Systems::basicCase2(QTextEdit *t){
    t->append("MAIN USE CASE 2 Allocation strat 2");
    int NPassengerUp=passengersUp2.size();
    int NPassengerDown=passengersDown2.size();
    if(NPassengerUp>0){
        for(size_t i=0;i<passengersUp2.size();i++){
            t->append("Passengers name "+QString::fromStdString(passengersUp2[i]->getName())+" is going up to floor Number "+QString::number(passengersUp2[i]->getDestFloor()));
            for(size_t j=0;j<elevators.size();j++){
               //Elevator Name
                t->append("Elevator #"+QString::number(j+1));
                //where it currently is
                int whereElevator=elevators[j]->getFloorNumber();
                t->append("Elevator is at Floor#"+QString::number(whereElevator));
                //send elevator to floor of passenger to pick them up
                if(!passengersUp2[i]->getStatus() && ((elevators[j]->getFloorNumber()<passengersUp2[i]->getFloor()) || (elevators[j]->getFloorNumber()==passengersUp2[i]->getFloor()))){
                   elevators[j]->move(passengersUp2[i]->getFloor());
                   t->append("Elevator at Floor #"+QString::number(elevators[j]->getFloorNumber()));
                   //check if elevator is moving or it is stopped at a floor
                   if((!elevators[j]->getMoving() || elevators[j]->getStopped())){
                       //check if passenger is assigned
                       if(!passengersUp2[i]->getStatus()){
                           passengersUp2[i]->setStatus(true);
                           elevators[j]->AddToDestFloor(passengersUp2[i]->getDestFloor());
                           std::vector<int> a = elevators[j]->getDestFloor();
                           for(size_t k=0;k<a.size();k++){
                               t->append("Destination Floors "+QString::number(a[k]));
                           }
                       }
                       elevators[j]->move(passengersUp2[i]->getDestFloor());
                   }
                }
                t->append("\n");
            }
            int elevatorSendToBase = (rand() % elevators.size());
            elevators[elevatorSendToBase]->move(1);
        }
        //int elevatorSendToBase = (rand() % elevators.size());
        //t->append(QString::number(elevatorSendToBase));
    }
    if(NPassengerDown>0){
        for(size_t i=0;i<passengersDown2.size();i++){
            t->append("Passengers name "+QString::fromStdString(passengersUp2[i]->getName())+" is going up to floor Number "+QString::number(passengersUp2[i]->getDestFloor()));
            for(size_t j=0;j<elevators.size();j++){
               //Elevator Name
                t->append("Elevator #"+QString::number(j+1));
                //where it currently is
                int whereElevator=elevators[j]->getFloorNumber();
                t->append("Elevator is at Floor#"+QString::number(whereElevator));
                //send elevator to floor of passenger to pick them up
                if(!passengersUp2[i]->getStatus() && ((elevators[j]->getFloorNumber()<passengersUp2[i]->getFloor()) || (elevators[j]->getFloorNumber()==passengersUp2[i]->getFloor()))){
                   elevators[j]->move(passengersUp2[i]->getFloor());
                   t->append("Elevator at Floor #"+QString::number(elevators[j]->getFloorNumber()));
                   //check if elevator is moving or it is stopped at a floor
                   if((!elevators[j]->getMoving() || elevators[j]->getStopped())){
                       //check if passenger is assigned
                       if(!passengersUp2[i]->getStatus()){
                           passengersUp2[i]->setStatus(true);
                           elevators[j]->AddToDestFloor(passengersUp2[i]->getDestFloor());
                           std::vector<int> a = elevators[j]->getDestFloor();
                           for(size_t k=0;k<a.size();k++){
                               t->append("Destination Floors "+QString::number(a[k]));
                           }
                       }
                       elevators[j]->move(passengersUp2[i]->getDestFloor());
                   }
                }
                t->append("\n");
            }
            int elevatorSendToBase = (rand() % elevators.size());
            elevators[elevatorSendToBase]->move(1);
        }
    }
    /*for(size_t i=0;i<elevators.size();i++){
        int whereElevator=elevators[i]->getFloorNumber();
        std::string name="";
        t->append("Elevator# "+QString::number(i+1)+" at Floor# "+QString::number(whereElevator));
        if(passengersDown2.size()==0 || passengersUp2.size()==0){
            if(NPassengerUp>0){
                for(size_t j=0;i<passengersUp2.size();j++){
                    if(elevators[i]->getCurLimit()<elevators[i]->getWeightLimit()){
                        name=passengersUp2[i]->getName();
                        t->append("Passenger Name"+QString::fromStdString(name)+"Enters Elevator and ");
                        //elevators[i]->destFloor.push_back(value)
                        elevators[i]->move(passengersUp2[i]->getFloor());
                        t->append("Elevator# "+QString::number(i+1)+" at Floor# "+QString::number(elevators[i]->getFloorNumber()));
                        elevators[i]->setCurLimit(passengersUp2[i]->getWeight());
                        elevators[i]->
                    }
                    else{
                        break;
                    }
                }
            }
            if(NPassengerDown>0){}
        }
    }*/
}

//allocation strategy 2
void Control_Systems::PopulatePassengers_up2(int floor,QTextEdit *t,int destn){
    if(floor==destn){
        t->append("PASSENGER IN SAME FLOORAS DESTN NO ELEVATOR ASSIGNED");
    }
    else{
        passengerCounter2=passengerCounter2+1;
        std::string passengerName="Passenger#"+std::to_string(passengerCounter2);
        passenger *p=new passenger(passengerName,floor,destn,50);
        passengersUp2.push_back(p);
        t->append(QString::number(passengerCounter2)+" Passenger Added from floor# "+QString::number(floor)+" Going UP - 2");
    }
}

void Control_Systems::PopulatePassengers_down2(int floor, QTextEdit *t,int destn){
    if(floor==destn){
        t->append("PASSENGER IN SAME FLOORAS DESTN NO ELEVATOR ASSIGNED");
    }
    else{
        passengerCounter2=passengerCounter2+1;
        std::string passengerName="Passenger#"+std::to_string(passengerCounter);
        passenger *p=new passenger(passengerName,floor,destn,50);
        passengersDown2.push_back(p);
        t->append(QString::number(passengerCounter2)+" Passenger Added from floor# "+QString::number(floor)+" Going DOWN - 2");
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
int Control_Systems::getPassengerSize(){
    return passengersUp.size()+passengersDown.size();
}
