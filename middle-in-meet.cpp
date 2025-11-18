#include <iostream>
#include <algorithm>
using namespace std;
//二分搜索：很大范围很多数的有序数组，先找到中间值，在左或右去找，再去找左或右的中间值....以此类推
int exist(int arr[],int n,int num)
{
    sort(arr,arr+n);
    if(arr == NULL ||  n == 0)
    {
        return false;
    }
    int ans = -1;
    int l = 0;
    int x = n-1;
    while(l <= x)
    {
        int m = l+((x-l)>>1);
        if(arr[m] <= num)
        {
            l = m+1;
            ans = m;
        }
        else if(arr[m] > num)
        {
            x = m-1;
        }
        
    }
    return ans;
}
int main()
{
    int arr[10] = {1,4,7,9,16,19,22,23,26,28};
    int num;
    cin >> num;
    cout << exist(arr,10,num);
    return 0;
}