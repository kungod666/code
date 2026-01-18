#include <iostream>
#include <vector>
#include <algorithm>
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
    vector<long> dp(W+1,0);
    // 0-1背包解法：每种物品只能取一次
    // 外层循环遍历物品
    for(long i = 0;i < N;i++)
    {
        // 内层循环逆序遍历容量，防止重复选取
        for(long j = W;j >=w[i];j--)
        {
            
            dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout << dp[W] << "\n";
}