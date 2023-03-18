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

//Find closest distance to passenger floor from elevator
int Control_Systems::findClosest(int passengerNumber,bool direction){
    int closestElevator=0;
    if(direction){
        //passengerNumber is floor Number of passenger
        if(elevators.size()>1){
            //int closest=elevators[0]->getFloorNumber();
            int closestDiff=std::abs(elevators[0]->getFloorNumber()-passengerNumber);
            if(closestDiff==0){
                return closestElevator;
            }
            for(size_t i=1;i<elevators.size();i++){
                int CurrentDiff = std::abs(elevators[i]->getFloorNumber()-passengerNumber);
                if(CurrentDiff<closestDiff){
                    closestElevator=i;
                    closestDiff=CurrentDiff;
                }
            }
            return closestElevator;
        }else{
            closestElevator=0;
            return closestElevator;
        }
    }else{
        if(elevators.size()>1){
            //int closest=elevators[0]->getFloorNumber();
            int closestDiff=std::abs(elevators[0]->getFloorNumber()-passengerNumber);
            if(closestDiff==0){
                return closestElevator;
            }
            for(size_t i=1;i<elevators.size();i++){
                int CurrentDiff = std::abs(elevators[i]->getFloorNumber()-passengerNumber);
                if(CurrentDiff<closestDiff){
                    closestElevator=i;
                    closestDiff=CurrentDiff;
                }
            }
            return closestElevator;
        }else{
            closestElevator=0;
            return closestElevator;
        }
    }
    //std::vector<passenger> p=
    return closestElevator;
}


//allocation strategy 1
//the elevator knows where it is at all times because it knows where it isn't strategy
void Control_Systems::basicCase(QTextEdit *t){
//using elevator centered strat
    //iterate over the passenger
    //first passenger we do not have any special case scenario -> EVEN FIRST PASSENGER Goes for this
    //other passenger onwards we find closest elevator to the passenger and they pick the person up
    t->append("MAIN USE CASE 1 Allocation strat 1\n");
    int NPassengerUp=passengersUp2.size();
    int NPassengerDown=passengersDown2.size();
    if(NPassengerUp>0){
        for(size_t i=0;i<passengersUp2.size();i++){
            t->append("Passengers name "+QString::fromStdString(passengersUp2[i]->getName())+" at floor# "+QString::number(passengersUp2[i]->getFloor())+" is going up to floor Number "+QString::number(passengersUp2[i]->getDestFloor()));
            int ElevatorNumber=findClosest(passengersUp2[i]->getFloor(),true);
            t->append("Elevator #"+QString::number(ElevatorNumber+1));
            int whereElevator=elevators[ElevatorNumber]->getFloorNumber();
            t->append("Elevator is currently at Floor#"+QString::number(whereElevator));
            //assign elevator to that floor and push destn to it and move elevator there
            //if(passengersUp2[i]->getFloor()<passengersUp2[i]->getFloor()){
            t->append("Elevator is now moving to Floor#"+QString::number(passengersUp2[i]->getFloor()));
            elevators[ElevatorNumber]->move(passengersUp2[i]->getFloor());
            t->append("Elevator is now at Floor #"+QString::number(elevators[ElevatorNumber]->getFloorNumber()));
            if((!elevators[ElevatorNumber]->getMoving() || elevators[ElevatorNumber]->getStopped())){
                if(!passengersUp2[i]->getStatus()){
                    passengersUp2[i]->setStatus(true);
                    t->append("Door Opening");
                    t->append("Audio System playing: Elevator has arrived");
                    elevators[ElevatorNumber]->AddToDestFloor(passengersUp2[i]->getDestFloor());
                    t->append("Passenger Name "+QString::fromStdString(passengersUp2[i]->getName())+" enters the elevator");
                    std::vector<int> a = elevators[ElevatorNumber]->getDestFloor();
                    t->append("Door Closing");
                    for(size_t k=0;k<a.size();k++){
                        t->append("Destination Floors "+QString::number(a[k]));
                    }
                }
                t->append("Elevator is now moving to Floor#"+QString::number(passengersUp2[i]->getDestFloor()));
                elevators[ElevatorNumber]->move(passengersUp2[i]->getDestFloor());
                //if(whereElevator==passengersUp2[i]->getDestFloor()){
                elevators[ElevatorNumber]->removeDestFloor();
                passengersUp2[i]->setStatus(false);
                t->append("\n");
            }
        }
    }
    if(NPassengerDown>0){
        for(size_t i=0;i<passengersDown2.size();i++){
            t->append("Passengers name "+QString::fromStdString(passengersDown2[i]->getName())+" at floor# "+QString::number(passengersDown2[i]->getFloor())+" is going up to floor Number "+QString::number(passengersDown2[i]->getDestFloor()));
            int ElevatorNumber=findClosest(passengersDown2[i]->getFloor(),true);
            t->append("Elevator #"+QString::number(ElevatorNumber+1));
            int whereElevator=elevators[ElevatorNumber]->getFloorNumber();
            t->append("Elevator is currently at Floor#"+QString::number(whereElevator));
            //assign elevator to that floor and push destn to it and move elevator there
            t->append("Elevator is now moving to Floor#"+QString::number(passengersDown2[i]->getFloor()));
            elevators[ElevatorNumber]->move(passengersDown2[i]->getFloor());
            t->append("Elevator is now at Floor #"+QString::number(elevators[ElevatorNumber]->getFloorNumber()));
            if((!elevators[ElevatorNumber]->getMoving() || elevators[ElevatorNumber]->getStopped())){
                if(!passengersDown2[i]->getStatus()){
                    passengersDown2[i]->setStatus(true);
                    t->append("Door Opening");
                    t->append("Audio System playing: Elevator has arrived");
                    elevators[ElevatorNumber]->AddToDestFloor(passengersDown2[i]->getDestFloor());
                    t->append("Passenger Name "+QString::fromStdString(passengersDown2[i]->getName())+" enters the elevator");
                    std::vector<int> a = elevators[ElevatorNumber]->getDestFloor();
                    t->append("Door Closing");
                    for(size_t k=0;k<a.size();k++){
                        t->append("Destination Floors "+QString::number(a[k]));
                    }
                }
                t->append("Elevator is now moving to Floor#"+QString::number(passengersDown2[i]->getDestFloor()));
                elevators[ElevatorNumber]->move(passengersDown2[i]->getDestFloor());
                //if(whereElevator==passengersUp2[i]->getDestFloor()){
                elevators[ElevatorNumber]->removeDestFloor();
                passengersDown2[i]->setStatus(false);
                t->append("\n");
            }
        }
    }
    else{
        t->append("NO PASSENGERS TO ASSIGN");
    }

}

void Control_Systems::basicCase2(QTextEdit *t){
    t->append("MAIN USE CASE 2 Allocation strat 2\n");
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
                t->append("Elevator is currently at Floor#"+QString::number(whereElevator));
                //send elevator to floor of passenger to pick them up
                if(!passengersUp2[i]->getStatus() && ((elevators[j]->getFloorNumber()<passengersUp2[i]->getFloor()) || (elevators[j]->getFloorNumber()==passengersUp2[i]->getFloor()))){
                   t->append("Elevator is now moving to Floor#"+QString::number(passengersUp2[i]->getFloor()));
                    elevators[j]->move(passengersUp2[i]->getFloor());
                   t->append("Elevator is now at Floor #"+QString::number(elevators[j]->getFloorNumber()));
                   //check if elevator is moving or it is stopped at a floor
                   if((!elevators[j]->getMoving() || elevators[j]->getStopped())){
                       //check if passenger is assigned
                       if(!passengersUp2[i]->getStatus()){
                           passengersUp2[i]->setStatus(true);
                           t->append("Door Opening");
                           t->append("Audio System playing: Elevator has arrived");
                           elevators[j]->AddToDestFloor(passengersUp2[i]->getDestFloor());
                           t->append("Passenger Name "+QString::fromStdString(passengersUp2[i]->getName())+" enters the elevator");
                           std::vector<int> a = elevators[j]->getDestFloor();
                           t->append("Door Closing");
                           for(size_t k=0;k<a.size();k++){
                               t->append("Destination Floors "+QString::number(a[k]));
                           }
                       }
                       t->append("Elevator is now moving to Floor#"+QString::number(passengersUp2[i]->getDestFloor()));
                       elevators[j]->move(passengersUp2[i]->getDestFloor());
                       elevators[j]->removeDestFloor();
                       passengersUp2[i]->setStatus(false);
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
            t->append("Passengers name "+QString::fromStdString(passengersDown2[i]->getName())+" is going down to floor Number "+QString::number(passengersDown2[i]->getDestFloor()));
            for(size_t j=0;j<elevators.size();j++){
               //Elevator Name
                t->append("Elevator #"+QString::number(j+1));
                //where it currently is
                int whereElevator=elevators[j]->getFloorNumber();
                t->append("Elevator is currently at Floor#"+QString::number(whereElevator));
                //send elevator to floor of passenger to pick them up
                if(!passengersDown2[i]->getStatus() && ((elevators[j]->getFloorNumber()>passengersDown2[i]->getFloor()) || (elevators[j]->getFloorNumber()==passengersDown2[i]->getFloor()))){
                  t->append("Elevator is now moving to Floor#"+QString::number(elevators[j]->getFloorNumber()));
                  elevators[j]->move(passengersDown2[i]->getFloor());
                  t->append("Elevator is now at Floor #"+QString::number(elevators[j]->getFloorNumber()));
                   //check if elevator is moving or it is stopped at a floor
                   if((!elevators[j]->getMoving() || elevators[j]->getStopped())){
                       //check if passenger is assigned
                       if(!passengersDown2[i]->getStatus()){
                           passengersDown2[i]->setStatus(true);
                           t->append("Door Opening");
                           t->append("Audio System playing: Elevator has arrived");
                           elevators[j]->AddToDestFloor(passengersDown2[i]->getDestFloor());
                           t->append("Passenger Name "+QString::fromStdString(passengersDown2[i]->getName())+" enters the elevator");
                           std::vector<int> a = elevators[j]->getDestFloor();
                           t->append("Door Closing");
                           for(size_t k=0;k<a.size();k++){
                               t->append("Destination Floors "+QString::number(a[k]));
                           }
                       }
                       t->append("Elevator is now moving to Floor#"+QString::number(passengersDown2[i]->getDestFloor()));
                       elevators[j]->move(passengersDown2[i]->getDestFloor());
                       elevators[j]->removeDestFloor();
                       passengersDown2[i]->setStatus(false);
                   }
                }
                t->append("\n");
            }
            //send elevator to top floor if passengers are still there
            int elevatorSendToTop = (rand() % elevators.size());
            elevators[elevatorSendToTop]->move(CountFloors);
        }
    }
}

//allocation strategy 2
void Control_Systems::PopulatePassengers_up2(int floor,QTextEdit *t,int destn){
    if(floor==destn){
        t->append("PASSENGER IN SAME FLOOR AS DESTN NO ELEVATOR ASSIGNED");
        //exit(0);
    }
    else if(floor>destn){
        t->append("PASSENGER IN FLOOR HIGHER THAN DESTN NO ELEVATOR ASSIGNED");
        //exit(0);
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
        t->append("PASSENGER IN SAME FLOOR AS DESTN NO ELEVATOR ASSIGNED");
        //exit(0);
    }
    else if(floor<destn){
        t->append("PASSENGER IN FLOOR LESSER THAN DESTN NO ELEVATOR ASSIGNED");
        //exit(0);
    }
    else{
        passengerCounter2=passengerCounter2+1;
        std::string passengerName="Passenger#"+std::to_string(passengerCounter2);
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
        if(elevators[i]->getDestFloor().size()>0){
            t->append("ALL PASSENGERS ARE EXITING THE ELEVATOR");
            for(size_t i=0;i<elevators[i]->getDestFloor().size();i++){
                elevators[i]->removeDestFloor();
            }
        }
        else{
            t->append("ALL PASSENGERS ARE EXITING THE ELEVATOR");
        }
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
        if(elevators[i]->getDestFloor().size()>0){
            t->append("ALL PASSENGERS ARE EXITING THE ELEVATOR");
            for(size_t i=0;i<elevators[i]->getDestFloor().size();i++){
                elevators[i]->removeDestFloor();
            }
        }
        else{
            t->append("ALL PASSENGERS ARE EXITING THE ELEVATOR");
        }
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

//ONLY ACTIVE IF ATLEAST 1 Passenger present
//When clicked HOLD THE ELEVATOR IN PLACE - print statement and show counter
//pick a random elevator and assign a passenger to it - remove destFloor after executing test case
//Either force push a passenger to the elevator or assign one from the passenger vector
//if CLOSE is pressed print - door closed before default time
//door open
//door close scenario

//OPEN DOOR CLOSE DOOR
void Control_Systems::DoorScenario(QTextEdit *t, bool instruction){
    int randomElevator=QRandomGenerator::global()->bounded(1,CountCars)-1;
    t->append("Elevator# "+QString::number(randomElevator));
    if(passengersUp2.size()>0 || passengersUp.size()>0){
        t->append("Elevator at Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
        if(passengersUp2.size()>0){
            elevators[randomElevator]->move(passengersUp2[0]->getFloor());
            t->append("Elevator now moving to Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
            t->append("Passenger Name "+QString::fromStdString(passengersUp2[0]->getName())+" enters elevator");
        }else{
            elevators[randomElevator]->move(passengersUp[0]->getFloor());
            t->append("Elevator now moving to Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
            t->append("Passenger Name "+QString::fromStdString(passengersUp[0]->getName())+" enters elevator");
        }
        if(instruction){
            t->append("DOOR OPEN IS PRESSED");
            d->setDoor(true);
            t->append("COUNTER");
            d->setDoorOpenTimer(20);
            for(int i=0;i<d->getDoorOpenTimer();i++){
                t->append(QString::number(i));
            }
            t->append("DOOR IS CLOSING");
            d->setDoor(false);
        }
        else{
            t->append("DOOR CLOSE IS PRESSED");
            d->setDoor(false);
            t->append("DOOR IS CLOSING");
            d->setDoorOpenTimer(10);
        }
    }
    else if(passengersDown2.size()>0 || passengersDown.size()>0){
        t->append("Elevator at Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
        if(passengersDown2.size()>0){
            elevators[randomElevator]->move(passengersDown2[0]->getFloor());
            t->append("Elevator now moving to Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
            t->append("Passenger Name "+QString::fromStdString(passengersDown2[0]->getName())+" enters elevator");
        }else{
            elevators[randomElevator]->move(passengersDown[0]->getFloor());
            t->append("Elevator now moving to Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
            t->append("Passenger Name "+QString::fromStdString(passengersDown[0]->getName())+" enters elevator");
        }
        if(instruction){
            t->append("DOOR OPEN IS PRESSED");
            d->setDoor(true);
            t->append("COUNTER");
            d->setDoorOpenTimer(20);
            for(int i=0;i<d->getDoorOpenTimer();i++){
                t->append(QString::number(i));
            }
            t->append("DOOR IS CLOSING");
            d->setDoor(false);
        }
        else{
            t->append("DOOR CLOSE IS PRESSED");
            d->setDoor(false);
            t->append("DOOR IS CLOSING");
            d->setDoorOpenTimer(10);
        }
    }
    else{
        t->append("NO PASSENGERS IS POPULATED PLEASE POPULATE PASSENGER DATA \nTHANK YOU!\n");
    }
}

int Control_Systems::getPassengerSize(){
    return passengersUp.size()+passengersDown.size();
}

void Control_Systems::callSafety(QTextEdit *t,int elevatorNumber, int passengerNumber,bool direction){
    t->append("Building Safety Has Responded");
    if(direction){
      elevators[elevatorNumber]->setStopped();
      t->append("ISSUE IS RESOLVED");
      t->append("Elevator moving to destn of passenger");
      elevators[elevatorNumber]->move(passengersUp2[passengerNumber]->getDestFloor());
    }
    //elevators[elevatorNumber]->move(pass)

}

void Control_Systems::helpButton(QTextEdit *t){
    int randomElevator=QRandomGenerator::global()->bounded(1,CountCars+1)-1;
    t->append("Elevator# "+QString::number(randomElevator));
    if(passengersUp2.size()>0 || passengersUp.size()>0){
        int randomPassenger=QRandomGenerator::global()->bounded(0,passengersUp2.size());
        t->append("Elevator at Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
        elevators[randomElevator]->move(passengersUp2[0]->getFloor());
        elevators[randomElevator]->setStopped();
        t->append("Elevator now moving to Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
        t->append("Passenger Name "+QString::fromStdString(passengersUp2[randomPassenger]->getName())+" enters elevator");
        t->append("THE HELP BUTTON IS PRESSED FOR ELEVATOR#"+QString::number(randomElevator));
        elevators[randomElevator]->setHelpButton(true);
        t->append("\nService are contacted and if no one responds in 5 seconds 911 is called\n");
        t->append("\nService are connected\n");
        //counter to simulate seconds and then when it hits 4 of 5 WE say service connected random generated value will forward scenario to cops
        int generateRandom=QRandomGenerator::global()->bounded(1,3);
        if (generateRandom==1){
            callSafety(t,randomElevator,randomPassenger,true);
            //elevators[randomElevator]->setStopped();
        }
        else{
            for(int i=1;i<=5;i++){
                t->append(QString::number(i)+" seconds");
                elevators[randomElevator]->move(safeFloor);
                elevators[randomElevator]->setStopped();
            }
            t->append("911 has been dialed\n Please wait for help while we move you to the safe floor");
        }

    }
    else if(passengersDown2.size()>0 || passengersDown.size()>0){
        int randomPassenger=QRandomGenerator::global()->bounded(0,passengersDown2.size());
        t->append("Elevator at Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
        elevators[randomElevator]->move(passengersDown2[0]->getFloor());
        elevators[randomElevator]->setStopped();
        t->append("Elevator now moving to Floor#"+QString::number(elevators[randomElevator]->getFloorNumber()));
        t->append("Passenger Name "+QString::fromStdString(passengersDown2[randomPassenger]->getName())+" enters elevator");
        t->append("THE HELP BUTTON IS PRESSED FOR ELEVATOR#"+QString::number(randomElevator));
        elevators[randomElevator]->setHelpButton(true);
        t->append("\nService are contacted and if no one responds in 5 seconds 911 is called\n");
        t->append("\nService are connected\n");
        //counter to simulate seconds and then when it hits 4 of 5 WE say service connected random generated value will forward scenario to cops
        int generateRandom=QRandomGenerator::global()->bounded(1,3);
        if (generateRandom==1){
            callSafety(t,randomElevator,randomPassenger,false);
            //elevators[randomElevator]->setStopped();
        }
        else{
            for(int i=1;i<=5;i++){
                t->append("911 has been dialed\n Please wait for help while we move you to the safe floor");
                elevators[randomElevator]->move(safeFloor);
                elevators[randomElevator]->setStopped();
            }
        }
    }
}
