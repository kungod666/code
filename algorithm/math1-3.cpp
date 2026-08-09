#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
bool sushu(int tp)
{
    for(int i = 2;i <=sqrt(tp);i++)
    {
        if(tp % i == 0) return false;
    }
    return true;
}
int main()
{
    int N;
    cin >> N;
    int count = 0;
    int tp;
    for(int i = 0 ;i < N;i++)
    {
        cin >> tp;
        if(sushu(tp)) count++;
    }
    cout << count <<"\n";
}