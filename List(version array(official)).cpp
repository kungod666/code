#include <iostream>
using namespace std;
int* Queue(int n)
{
    int* queue = new int[n];
    return queue;
}
void offer(int* queue,int& r)
{
    int tp;
    cin >> tp;
    queue[r++] = tp;
}
int head(int* queue,int& l)
{
    return queue[l];
}
int tail(int* queue,int& r)
{
    return queue[r-1];
}
void poll(int* queue,int& l)
{
    cout << queue[l] << "\n";
    l++;
}
bool isEmpty(int l,int r)
{
    return l == r;
}
int main()
{
    return 0;
}