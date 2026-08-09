#include "snake.h"
#include <conio.h>
#include "food.h"
Point Snake::getHead(){
    return body.back();
}
void Snake::Move(){
    Point temp = Snake::getHead();
    switch(dir){
        case UP:
        body.emplace_back(temp.getX(),temp.getY()-1);
        break;
        case DOWN:
        body.emplace_back(temp.getX(),temp.getY()+1);
        break;
        case LEFT:
        body.emplace_back(temp.getX()-1,temp.getY());
        break;
        case RIGHT:
        body.emplace_back(temp.getX()+1,temp.getY());
    }
    body.back().Print();
}

int Snake::getScore()const{
    return this->score;
}
Snake::Snake(){
    dir = RIGHT; //默认往右走
    score = 0;
    body.emplace_back(12,14);
    body.emplace_back(13,14);
    body.emplace_back(14,14);
}

std::deque<Point> Snake::getBody()const{
    return body;
}

bool Snake::changeDirection() {
    if (_kbhit()) {
        char c = _getch();
        if (c == -32 || c == 224) {   // 兼容两种扫描码
            c = _getch();
            switch (c) {
            case 72: if (dir != DOWN) dir = UP; break;
            case 80: if (dir != UP) dir = DOWN; break;
            case 75: if (dir != RIGHT) dir = LEFT; break;
            case 77: if (dir != LEFT) dir = RIGHT; break;
            default: break;
            }
        }
        else if (c == 'w' || c == 'W') {
            if (dir != DOWN) dir = UP;
        }
        else if (c == 's' || c == 'S') {
            if (dir != UP) dir = DOWN;
        }
        else if (c == 'a' || c == 'A') {
            if (dir != RIGHT) dir = LEFT;
        }
        else if (c == 'd' || c == 'D') {
            if (dir != LEFT) dir = RIGHT;
        }
        else if (c == 27) {
            return false;
        }
        // 清空可能残留的按键（避免缓冲区干扰）
        while (_kbhit()) _getch();
    }
    return true;
}

void Snake::NormalMove(){
    Move();
    body.front().Clear();
    body.pop_front();
}

bool Snake::hitItself(){
    Point head =body.back();
    int cnt = 1;
    for(auto& point:body){
        if(!(head.getX() == point.getX()&&head.getY() == point.getY())){
            //注，此处不可直接用head == point，因为未经过运算符重载，不知如何比较
            cnt++;
        }
        else break;
    }
    if(cnt == body.size()) return false;
    else return true;
}
//根据这个函数来++score
bool Snake::getFood(const Food& food){
    if(body.back() == food.foodpos){
        return true;
    }
    return false;
}

void Snake::initSnake(){
    for(auto& it : body){
        it.Print();
    }
}

bool Snake::hitWall(){
    for(auto& it : body){
        if(it.getX() < 2 || it.getX() > 29||it.getY()<2||it.getY()>29) return true;
    }
    return false;
}