#ifndef ELEVATORBUTTON_H
#define ELEVATORBUTTON_H
#include <vector>
#include <string>
class elevatorButton{
private:
    bool illuminate;
    bool isPressed;// this function is for the control systems to interact with and see wether the passenger on the floor had pressed the call button for the elevator
    std::string Direction;// which direction the elevator will be going in top or bottm ONLY TWO ALLOWED INPUTS
public:
    elevatorButton(std::string);
    ~elevatorButton();
    void pressButton(std::string);// This Button will call the elevator and inform the control system that a passenger on the floor had interacted with the system
    bool getIllumniate();
    bool getPressed();
    bool setIllumniate();
    bool setPressed();
    std::string getDirection();
    std::string setDirection(std::string);
};

#endif // ELEVATORBUTTON_H
