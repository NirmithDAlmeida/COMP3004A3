#ifndef DOOR_H
#define DOOR_H

class Door{
private:
    bool doorOpen;//true door open false door close
    bool KeepDoorOpen;// this is the elevator button to keep door open false is close quicker
    bool closeDoor;// this is the elevator button to close quicker
    int doorOpenTimer =10;//this is the
public:
    Door();
    void print();//display status of doors
    bool getDoorOpen();
    bool getKeepDoorOpen();
    bool getCloseDoor();
    bool getDoorOpenTimer();//no setters hard coded into system
    bool setDoorOpen();
    bool setKeepDoorOpen();
    bool setCloseDoor();
};

#endif // DOOR_H
