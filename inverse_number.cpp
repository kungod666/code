#include <iostream>
#include <vector>
#include <utility>
#include <climits>
using namespace std;
long merge(vector<long>& A,long left,long mid,long right)
{
    long inverse = 0;
    long n1 = mid-left;
    long n2 = right - mid;
    vector<long> L(n1+1);
    vector<long> R(n2+1);
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    for(long i = 0 ;i < n1;i++)
    {
        L[i] = A[left+i];
    }
    for(long i = 0;i < n2;i++)
    {
        R[i] = A[mid+i];
    }
    long a,b,c;
    a = 0;
    b = 0;
    c = left;
    while(c < right)
    {
        if(L[a] > R[b])
        {
            A[c] = R[b];
            inverse += n1-a;
            b++;
            c++;
        }
        else if(L[a] <= R[b])
        {
            A[c] = L[a];
            a++;
            c++;
        }
    }
    return inverse;
}
long merge_sort(vector<long>& A,long left,long right)
{
    long mid = left + (right-left)/2;
    long inverse = 0;
    if(left + 1 < right)//这样设置防止l=0,r=1后无限递归
    {
        inverse += merge_sort(A,left,mid);
        inverse += merge_sort(A,mid,right);
        inverse += merge(A,left,mid,right);
    }
    return inverse;
}
int main()
{
    long n;
    cin >> n;
    vector<long> A(n);
    for(long i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    long num = merge_sort(A,0,n);
    cout << num << "\n";
    return 0;
}