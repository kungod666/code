#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
/*1 ≤ N ≤ 100
1 ≤ vi ≤ 100
1 ≤ wi ≤ 10,000,000
1 ≤ W ≤ 1,000,000,000*/
//考虑价值导向dp
using namespace std;
int main()
{
    long N,W;
    cin >> N >> W;
    vector<long> v(N);
    vector<long> w(N);
    for(long i = 0;i < N;i++)
    {
        cin >> v[i] >> w[i];
    }
    vector<long> dp(10001,LONG_MAX);
    dp[0] = 0;
    //无论0-1还是完全，都是外层循环遍历物品
    for(long i = 0;i < N;i++)
    {
        for(long j = 10000;j >=0;j--)
        {
            if(dp[j-v[i]] != LONG_MAX)
            {
                dp[j] = min(dp[j],dp[j-v[i]]+w[i]);
            }
        }
    }
    long m;
    for(m = 10000;m >=0;m--)
    {
        if(dp[m] <= W) break;
    }
    cout << m << "\n";
}