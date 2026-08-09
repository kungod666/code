#include <iostream>
#include <vector>
using namespace std;
vector<int> bubblesort(vector<int> A,int n)
{
    int count = 0;
    for(int i = 0;i < n-1;i++)
    {
        for(int j = n-1;j > i;j--)
        {
            if(A[j-1] > A[j]) 
            {
                swap(A[j-1],A[j]);
                count++;
            }
        }
    }
    for(auto it : A)
    {
        cout << it << " ";
    }
    cout << "\n";
    cout << count;
    return A;
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
    bubblesort(A,n);
    return 0;
}