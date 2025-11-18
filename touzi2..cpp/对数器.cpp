#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <string>
#include <bitset>
#include <map>
#include <algorithm>
#include <math.h>
using namespace std;
void bubble(int* arr1,int n)
{
    for(int i = 0;i < n-1;i++)
    {
        for(int j = 0;j < n-1-i;j++)
        {
            if(arr1[j] > arr1[j+1])
            {
                swap(arr1[j],arr1[j+1]);
            }
        }
    }
}
int* generateArray(int n,int maxValue)
{
    int* arr = new int[n];
    for(int i = 0;i < n;i++)
    {
        arr[i] = (rand()%maxValue)+1;
    }
    return arr;
}
int* copyArray(int* arr1,int n)
{
    int* arr2 = new int[n];
    for(int i = 0;i < n;i++)
    {
        arr2[i] = arr1[i];
    }
    return arr2;
}
void printArray(int* arr,int n)
{
    for(int i = 0;i < n;i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}
bool comperator()
{
    int testTime = 100;//测试次数
    int maxSize = 100;//最大测试规模
    int maxValue = 100;//最大值
    for(int i = 1;i <=testTime;i++)
    {
        int n = (rand()%100)+1;
        int* arr1 = generateArray(n,maxValue);
        int* arr2 = copyArray(arr1,n);
        int* arr3 = copyArray(arr1,n);
        bubble(arr1,n);
        sort(arr2,arr2+n);
        sort(arr3,arr3+n);
        for(int j = 0;j < n;j++)
        {
            if(arr1[j] != arr2[j] || arr1[j] != arr3[j])
            {
                printArray(arr1,n);
                printArray(arr2,n);
                printArray(arr3,n);
                return false;
            }
        }
    }
    return true;
}
int main()
{
    
    return 0;
}
