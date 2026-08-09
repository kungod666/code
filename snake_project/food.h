#ifndef FOOD_H
#define FOOD_H
#include "tools.h"
#include "point.h"
class Snake;
class Food{
    public:
    Point foodpos;
    public:
    void foodRand(const Snake& snake);
    Point foodPosition();
    friend class Snake;
};
#endif