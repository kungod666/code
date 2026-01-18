#include <iostream>
#include <vector>
using namespace std;
//完全背包问题
int main()
{
    int N,W;
    cin >> N >> W;
    vector<int> v(N);
    vector<int> w(N);
    vector<int> dp(W+1,-1);
    dp[0] = 0;
    for(int i = 0;i < N;i++)
    {
        cin >> v[i] >> w[i];
    }
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < W+1;j++)
        {
            if(j-w[i] < 0) continue;
            if(dp[j-w[i]] != -1)
            {
                dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
            }
        }
    }
    int max = dp[W];
    for(int i = W-1;i >= 0;i--)
    {
        if(dp[i] > max) max = dp[i];
    }
    cout << max << "\n";
}