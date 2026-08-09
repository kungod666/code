#include "snake.h"
#include "food.h"
#include "point.h"
#include "map.h"
#include "tools.h"
#include <thread>
#include <windows.h>
#include <iostream>
int main() {
    initMap();
    Snake snake;//初始化
    snake.initSnake();
    int temp = snake.getScore();
    Food food;
    food.foodpos = Point(15,15);
    food.foodRand(snake);
    while(!snake.hitItself()&&!snake.hitWall()){
        SetCursorPosition(0, 21);
        std::cout << snake.getScore();
        if(!(snake.getScore() == temp)){
            food.foodRand(snake);
            temp = snake.getScore();
        }
        snake.changeDirection();
        if(snake.getFood(food)){
            snake.Move();
            food.foodpos.Clear();
            snake.getBody().back().Print();
            snake.score++;
            food.foodRand(snake);
            temp = snake.getScore();
        }
        else snake.NormalMove();
        Sleep(200);
    }
    system("pause");
    return 0;
}