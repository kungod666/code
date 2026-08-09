#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int Merge(vector<int>& A,int left,int mid,int right)
{
    int count = 0;
    int n1 = mid -left;
    int n2 = right - mid;
    vector<int> L(n1+1);
    vector<int> R(n2+1);
    for(int i = 0;i < n1 ; i++)
    {
        L[i] = A[left+i];
    }
    for(int i = 0;i < n2;i++)
    {
        R[i] = A[mid+i];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i,j,k;
    i = 0;
    j = 0;
    k = left;
    for(;k < right;k++)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
            count++;
        }
        else if(L[i] > R[j]) 
        {
            A[k] = R[j];
            j++;
            count++;
        }
    }
    return count;
}
int Merge_Sort(vector<int> & A,int left,int right)
{
    int mid;
    int count = 0;
    if(left+1 < right)
    {
        mid = (left + right) /2;
        count+=Merge_Sort(A,left,mid);
        count+=Merge_Sort(A,mid,right);
        count+=Merge(A,left,mid,right);
    }
    return count;
}
int main()
{
    int n;
    cin >> n;
    vector<int> A(n);
    for(int i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    int count = Merge_Sort(A,0,n);
    for(auto it : A)
    {
        cout << it << " ";
    }
    cout << "\n";
    cout << count;

    return 0;
}