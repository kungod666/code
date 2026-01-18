#include <iostream>
#include <vector>
using namespace std;
int cnt;
void insertionSort(vector<int>& A,int n,int g)
{
    for(int i = g;i < n;i++)
    {
        int v = A[i];
        int j = i-g;
        while(j>=0&&A[j]>v)
        {
            A[j+g] = A[j];
            j = j -g;
            cnt++;
        }
        A[j+g] = v;
    }
}
void shellSort(vector<int>& A,int n)
{
    cnt = 0;
    int m = 1;
    int op = 1;
    vector<int> G;
    G.push_back(1);
    while(3*op+1<n)
    {
        op = op*3+1;
        G.push_back(op);
        m++;
    }
    cout << m << "\n";
    for(auto it = G.rbegin();it!=G.rend();it++)
    {
        cout << *it << " ";
    }
    cout << "\n";
    for(int i = m-1;i >= 0;i--)
    {
        insertionSort(A,n,G[i]);
    }
    cout << cnt << "\n";
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
    shellSort(A,n);
    for(auto it : A)
    {
        cout << it << "\n";
    }
    return 0;
}