#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main()
{
    ll N,W;
    cin >> N >> W;
    vector<ll> dp(W+1,-1);
    dp[0] = 0;
    ll count  = 0;
    while(count < N)
    {
        ll v,w,num;
        cin >> v >> w >> num;
        ll k = 1;
        while(num > 0)
        {
            ll use = min(k,num);
            ll group_val = use*v;
            ll group_wei = use*w;
            for(ll j = W;j >= group_wei;j--)
            {
                if(dp[j-group_wei] != -1) dp[j] = max(dp[j],dp[j-group_wei] + group_val);
            }
            num -=use;
            k <<=1;
        }
        count++;
    }
    ll max = dp[W]; //W不再一定是最大，需遍历得到最大价值
    for(int j = W-1;j>=0;j--)
    {
        if(dp[j] > max) max = dp[j];
    }
    cout << max << "\n";
}