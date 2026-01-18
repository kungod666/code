#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <algorithm>
using namespace std;
vector<vector<pair<char,int>>> C;
void bubblesort(vector<pair<char,int>> A,int n)
{
    for(int i = 0;i < n-1;i++)
    {
        for(int j = n-1;j > i;j--)
        {
            if(A[j-1].second > A[j].second) 
            {
                swap(A[j-1],A[j]);
            }
        }
    }
    C.push_back(A);
}
void selection_sort(vector<pair<char,int>> A,int n)
{
    for(int i = 0;i < n-1;i++)
    {
        int mini = i;
        for(int j = i+1;j < n;j++)
        {
            if(A[j].second < A[mini].second)
            {
                mini = j;
                //此举是为了不断将最小元素移至i位置
            }
        }
        if(mini != i)
        {
            swap(A[i],A[mini]);
        }
    }
    C.push_back(A);
}
int main()
{
    int n;
    cin >> n;
    vector<pair<char,int>> A(n);
    set<set<int>> index; 
    for(int i = 0; i < n;i++)
    {
        cin >> A[i].first >> A[i].second;
    }
    bubblesort(A,n);
    for(int i = 0;i < n;i++)
    {
        cout << C[0][i].first << C[0][i].second << " ";
    }
    cout << "\n";
    cout << "Stable\n";
    selection_sort(A,n);
    for(int i = 0;i < n;i++)
    {
        cout << C[1][i].first << C[1][i].second << " ";
    }
    cout << "\n";
    for(int i = 0;i < n;i++)
    {
        if(C[0][i].first != C[1][i].first)
        {
            cout << "Not stable\n";
            return 0;
        }
    }
    cout << " Stable\n";
    return 0;
}