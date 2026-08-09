#include <iostream>
using namespace std;
/*数组实现双端队列：premeter:head（l)tail(r),size,k
构造循环队列，head &tail illustrate pos
1):l == 0->move l to k-1
2):l!=0->locate digit in l-1,and l--
r the same as l*/
#define k 10
int arr[k];
int l = 0;
int r = 0;
int a_size = 0;
void push_back()
{
    if(a_size == k)
    {
        cout << "已满不准" << "\n";
        return;
    }
    int tp;
    cin >> tp;
    if(r == k-1)
    {
        r = 0;
        arr[r] = tp;
        a_size++;
        return;
    }
    else
    {
        arr[++r] = tp;
        a_size++;
    }
}
void push_front()
{
    if(a_size == k)
    {
        cout << "已满不准" << "\n";
        return;
    }
    int tp;
    cin >> tp;
    if(l == )
    {
        l = k-1;
        arr[l] = tp;
        a_size++;
        return;
    }
    else
    {
        arr[++l] = tp;
        a_size++;
    }
}
void pop_back()
{
    if(a_size==0)
    {
        cout << "不可弹出" << "\n";
        return;
    }
    cout << arr[r] << "\n";
    if(r == 0)
    {
        r = k-1;
        a_size--;
    }
    else
    {
        r--;
        a_size--;
    }
}
void pop_front()
{
    if(a_size==0)
    {
        cout << "不可弹出" << "\n";
        return;
    }
    cout << arr[r] << "\n";
    if(r == k-1)
    {
        l = 0;
        a_size--;
    }
    else
    {
        l++;
        a_size--;
    }
}
int main()
{
}