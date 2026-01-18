#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
int partition(vector<int>& A,vector<char>& B,int p,int r)
{
    int x = A[r];
    int i = p-1;
    for(int j = p;j < r;j++)
    {
        if(A[j] <= x)
        {
            i++;
            swap(A[i],A[j]);
            swap(B[i],B[j]);
        }
    }
    swap(A[i+1],A[r]);
    swap(B[i+1],B[r]);
    return i+1;
}
void quicksort(vector<int>& A,vector<char>& B,int p,int r)
{
    int q;
    if(p < r)
    {
        q = partition(A,B,p,r);
        quicksort(A,B,p,q-1);
        quicksort(A,B,q+1,r);
    }
}
int main()
{
    int n;
    cin >> n;
    vector<int> A(n);//装整数
    vector<char> B(n);//装字符
    vector<pair<int,char>> C(n);
    for(int i = 0;i < n;i++)
    {
        cin >> B[i] >> A[i];
        C[i].first = A[i];
        C[i].second = B[i];
    }
    quicksort(A,B,0,n-1);
    stable_sort(C.begin(),C.end(),[](const pair<int,char>& a,const pair<int,char>& b)
    {
        return a.first < b.first;
    });
    int panbie = 1;
    for(int i = 0;i < n;i++)
    {
        if(C[i].second != B[i])
        {
            cout << "Not stable\n";
            panbie = 0;
            break;
        }
    }
    if(panbie) cout << "Stable\n";
    for(int i = 0;i < n;i++)
    {
        cout << B[i] << " " << A[i] << "\n";
    }
}