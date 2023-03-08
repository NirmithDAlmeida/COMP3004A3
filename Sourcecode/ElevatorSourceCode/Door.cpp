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
