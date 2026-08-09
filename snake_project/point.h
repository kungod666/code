#ifndef POINT_H
#define POINT_H

class Food;
class Point{
private:
    int x;
    int y;
public:
    Point(int X,int Y):x(X),y(Y){}

    Point() : x(0), y(0) {}
    
    bool operator==(const Point& other) const{
        return x == other.x&& y == other.y;
    }

    int getX()const{ //规定为const，因为本就不该修改成员状态
        return this->x;
    }

    int getY()const{
        return this->y;
    }

    void Clear();

    void Print();

    void PrintFood();

    friend class Food;
};

#endif