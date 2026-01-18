#include <iostream>
#include <utility>
#include <vector>
using namespace std;
int main()
{
    int N,W;
    cin >> N >> W;
    vector<int> v(N);
    vector<int> w(N);
    for(int i = 0;i <N;i++)
    {
        cin >> v[i] >> w[i];
    }
    vector<vector<int>> dp(N+1,vector<int>(W+1,0));
    //dp[i][j]求的是取前i件物品，背包容量为j时的最大值
    for(int i = 1;i <= N;i++)
    {
        for(int j = 1;j <= W;j++)
        {
            if(j < w[i-1])
            {
                dp[i][j] = dp[i-1][j];
            }
            else 
            {
                
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-w[i-1]]+v[i-1]);
            }
        }
    }
    cout << dp[N][W] << "\n";
    return 0;
}