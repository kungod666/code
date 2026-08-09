#include "tools.h"
#include <stdio.h>
#include <windows.h>
void SetWindowSize(int cols, int lines){
    system("title snakeGame");
    char cmd[30];
    sprintf_s(cmd,"mode con col=%d lines=%d",cols,lines);
    system(cmd);
}

void SetCursorPosition(int x, int y){
    COORD len;
    len.X = x;
    len.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), len);
}

void SetCursorColor(int colorID){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
