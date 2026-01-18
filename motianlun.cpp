#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
ull n,x;
ull solution(vector<ull>& A)
{
    sort(A.begin(),A.end());
    ull count = 0;
    for(int i = 0,j = A.size()-1;i <= j;)
    {
        if(A[j]+A[i]<=x)
        {
            i++;
            j--;
        }
        else j--;
        count++;
    }
    return count;
}
int main()
{
    cin >> n >> x;
    vector<ull> A(n);
    for(int i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    cout << solution(A)  << "\n";
    return 0;
}