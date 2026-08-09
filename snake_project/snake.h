#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include "point.h"
class Food;
class Point;
class Snake{
    private:
    std::deque<Point> body;
    public:
    enum Direction {UP,DOWN,LEFT,RIGHT};
    int score;
    Direction dir;
    Snake();
    void initSnake();//初始绘制函数
    void Move();

    void NormalMove();

    std::deque<Point> getBody()const;

    Point getHead();

    bool changeDirection();

    bool hitItself(); 

    bool getFood(const Food& food);

    bool hitWall();

    int getScore()const;

    friend class Food;
};
#endif