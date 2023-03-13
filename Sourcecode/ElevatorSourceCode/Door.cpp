#include "Door.h"
Door::Door(){
    doorOpen=false;//true door open false door close
    KeepDoorOpen=false;// this is the elevator button to keep door open false is close quicker
    closeDoor=true;
}
void Door::setDoor(bool a){
    doorOpen=a;
}
bool Door::getDoorOpen(){
    return doorOpen;
}
//bool Door::get
bool Door::getKeepDoorOpen(){
    return KeepDoorOpen;
}
int Door::getDoorOpenTimer(){
    return doorOpenTimer;
};//no setters hard coded into system
void Door::setKeepDoorOpen(){
    KeepDoorOpen=!KeepDoorOpen;
}
void Door::setCloseDoor(){
    closeDoor=!closeDoor;
}
void Door::setDoorOpenTimer(int a){
    doorOpenTimer=a;
}
