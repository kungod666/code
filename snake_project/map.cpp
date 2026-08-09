#include "map.h"
#include "tools.h"
#include <iostream>
#define COLS 30
#define LINES 30
void initMap(){
    SetWindowSize(COLS, LINES);
    for(int i = 1;i <=30;i++){
        SetCursorPosition(1, i);
        std::cout << "$";
    }
    int arr[2] = {1,30};
    for(int i = 2;i <=29;i++){
        for(int j = 0;j <2;j++){
            SetCursorPosition(i, arr[j]);
            std::cout << "$";
        }
    }
    for(int i = 1;i <=30;i++){
        SetCursorPosition(30, i);
        std::cout << "$";
    }
    SetCursorPosition(0,20);
    std::cout << "Score:";
}