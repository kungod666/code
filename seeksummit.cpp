#include <iostream>
using namespace std;
int seeksummit(int* arr,int n)
{
    if(n == 1)
    {
        return 0;
    }
    if(n >=2)
    {
        if(arr[0] > arr[1]) return 0;
        if(arr[n-1] > arr[n-2]) return n-1;
        int l = 1;
        int r = n-2;
        int m;
        while(l <= r)
        {
            m = (l+r)/2;
            if(arr[m] >arr[m-1] && arr[m] > arr[m+1])
            {
                return m;
            }
            else if(arr[m] < arr[m-1])
            {
                r = m-1;
            }
            else
            {
                l = m+1;
            }
        }
    }
    return -1;
}
int main()
{
    int n;
    cin >> n;
    int* arr = new int[n];
    for(int i = 0;i < n;i++)
    {
        cin >> arr[i];
    }
    cout << seeksummit(arr,n);
    delete[] arr;
    return 0;
}