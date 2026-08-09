#include "point.h"
#include "tools.h"
#include <iostream>
void Point::Clear(){
    SetCursorPosition(this->getX(), this->getY());
    std::cout << " ";
}

void Point::Print(){
    SetCursorPosition(this->getX(), this->getY());
    SetCursorColor(14);
    std::cout << "@";
}

void Point::PrintFood(){
    SetCursorPosition(this->getX(), this->getY());
    SetCursorColor(12);
    std::cout<< "#";
}