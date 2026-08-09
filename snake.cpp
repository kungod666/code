#include <iostream>
class Player{
    private:
    float x,y;
    float speed;
    public:
    Player(float tpx,float tpy,float tspeed):x(tpx),y(tpy),speed(tspeed){};
    ~Player();
};

template<typename T>
void print(T value){
    std::cout << value << std::endl;
}
//template,not code,only be created when calling it
//based on how you use it

template<typename T,int N>
class Array{
    public:
    int arr[N];
};
int main(){
    print(5);
    print<float>(5.5f);
    print("Hello");
    Array<int,5> arr;
    std::cout << arr.arr[1];
    return 0;
}