#include <iostream>
using namespace std;
//stack即为弹匣，后进先出，数组实现即可
/*1.加元素，放在size,size++
2.弹出，弹出size-1，size--*/
bool isEmpty(int size)
{
    return size == 0;
}
void push(int* stack,int size)
{
    int tp;
    cin >> tp;
    stack[size++] = tp;
}
int pop(int* stack,int& size)
{
    return stack[--size];//优雅的代码，同时完成返回与缩容
}
int peek(int* stack,int size)
{
    return stack[size-1];
}
int main()
{
    int n;
    cin >> n;
    int size = 0;
    int stack[n];
}