#include <iostream>
#include <vector>
using namespace std;
void insertionsort(vector<int> A,int size)
{
    for(auto it : A)
    {
        cout << it << " ";
    }
    cout << "\n";
        for(int i = 1;i < size;i++)
    {
        int tp = A[i];
        int j = i-1;
        while(A[j]>tp&&j>=0)
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = tp;
        for(auto it : A)
        {
            cout << it << " ";
        }
        if(i!=size-1) cout << "\n"; 
    }
}
int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0;i < N;i++)
    {
        cin >> A[i];
    }
    insertionsort(A,N);
    return 0;
}