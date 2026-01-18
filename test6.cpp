#include <iostream>
using namespace std;
int* xuanzhuan90(int* arr,int n)
{
    int* tp = new int[n*n];
    for(int i = n-1;i >=0;i--)
    {
        for(int j = (n*n)-1-(n-1-i)*n;j >=n-1-(n-1-i)*n;j--)
        {
            tp[j] = arr[i+((n*n)-1-(n-1-i)*n-j)*n];
        }
    }
    return tp;
}
int main()
{
    int n,k;
    while(cin >> n>>k)
    {
        int* arr = new int[n*n];
        for(int i = 0;i < n*n;i++)
        {
            cin >> arr[i];
        }
        int* rece = arr;
        for(int i = 0;i < k%4;i++)
        {
            rece = xuanzhuan90(rece,n);
        }
        for(int i = 1;i <= n*n;i++)
        {
            cout << rece[i-1] << " ";
            if(i%n == 0&&i != n*n) cout << "\n";
        }
    }
}