#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include<iostream>

class display{
public:
    display();
    ~display();
    void printText(std::string,std::string="safety");//to print out final statements
};

#endif // DISPLAYWINDOW_H
