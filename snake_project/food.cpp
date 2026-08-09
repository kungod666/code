#include "food.h"
#include "point.h"
#include "snake.h"
#include "tools.h"
#include <random>
Point Food::foodPosition(){
    return foodpos;
}

void Food::foodRand(const Snake& snake){
    // 随机设备，用于获得真随机种子
    std::random_device rd;
    // 梅森旋转引擎，用 rd() 作为种子
    std::mt19937 gen(rd());
    // 均匀分布，整数区间 [2, 29]
    std::uniform_int_distribution<int> dis(2, 29);
    int ordi_x;
    int ordi_y;
    while(true){
    ordi_x = dis(gen);
    ordi_y = dis(gen);
    int flag = 0;
    for(auto& point : snake.body){
        if(ordi_x == point.getX() && ordi_y == point.getY()){
            flag = 1;
            break;
        }
    }
    if(flag) continue;
    break;
    }
    foodpos.x = ordi_x;
    foodpos.y = ordi_y;

    SetCursorPosition(ordi_x, ordi_y);
    foodpos.PrintFood();
    
}