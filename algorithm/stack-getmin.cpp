#include <iostream>
using namespace std;
/*背景：要求在栈中实现getmin（）操作（取得栈中元素最小值）
算法：data栈与min栈*/
int left1 = 0;
int right1 = 0;
int left2 = 0;
int right2 = 0;
void push(int* data,int* min)
{
    int tp;
    cin >> tp;
    data[right1++] = tp;
    if(right2 == 0)
    {
        min[right2++] = tp;
    }
    else if(right2 != 0)
    {
        if(tp < min[right2])
        {
            min[right2++] = tp;
        }
        else {
            min[right2++] = min[right2-1];
        }
    } 
}
int getMin(int* min)
{
    return min[right2-1];
}
int main()
{
    int n;
    cin >> n;
    int* data = new int[n];
    int* min = new int[n];
}