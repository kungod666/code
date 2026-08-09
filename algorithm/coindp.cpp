#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
/*使用面额为d1、d2、…、dm美分的硬币，
找出要兑换n美分的最小硬币数。这些硬币可以使用任意次数。*/
int main()
{
    int n,m;
    cin >> n >> m;
    vector<int> A(m);
    cin >> A[0];
    int max_num = A[0];
    for(int i = 1;i < m;i++)
    {
        cin >> A[i];
        if(A[i] > max_num) max_num = A[i];
    }
    vector<int> dp(n+1,INT_MAX);
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 0;i <= n;i++)
    {
        for(int j = 0;j < m;j++)
        {
            if(i - A[j] >= 0)
            {
               if(dp[i-A[j]] != INT_MAX)
               {
                   dp[i] = min(dp[i],dp[i-A[j]]+1);
               }
            }
        }
    }
    cout << dp[n] << "\n";
}