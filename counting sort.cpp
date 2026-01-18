#include <iostream>
#include <vector>
using namespace std;
//o(n+k)
vector<int> counting_sort(vector<int>& A,int k)
{
    vector<int> C(k+1,0);
    vector<int> B(A.size());
    for(int j = 0;j < A.size();j++)
    {
        C[A[j]] +=1;
    }
    for(int i = 1;i <= k;i++)
    {
        C[i] = C[i] + C[i-1];
    }
    for(int i = A.size()-1;i >= 0;i--) // 倒序遍历保证排序稳定性！
    {
        B[(C[A[i]]--)-1] = A[i];
    }
    return B;
}
int main()
{
    int n;
    cin >> n;
    vector<int> A(n);
    int max = 0;
    for(int i =0;i < n;i++)
    {
        cin >> A[i];
        if(max < A[i]) max = A[i];
    }
    A = counting_sort(A,max);
    for(auto it = A.begin();it != A.end();it++)
    {
        cout << *it;
        if(it != --A.end()) cout << " ";
    }
}