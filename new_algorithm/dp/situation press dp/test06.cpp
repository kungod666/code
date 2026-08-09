/*某乡有 n 个村庄，有一个售货员，他要到各个村庄去售货，
各村庄之间的路程 s 
i,j是已知的，且 A 村到 B 村与 B 村到 A 村的路大多不同。
为了提高效率，他从商店出发到每个村庄一次，然后返回商店所在的村，
假设商店所在的村庄为 1，他不知道选择什么样的路线才能使所走的路程最短。
请你帮他选择一条最短的路。*/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<vector<int>> village(n,vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin >> village[i][j];
        }
    }
    int total = 1 << n;
    vector<vector<int>> dp(total,vector<int>(n,INT_MAX));
    //dp[mask][i]:在已经访问过mask掩码对应村庄情况下,到i节点距离
    dp[1][0] = 0;
    for(int mask = 1;mask < total;mask++){
        for(int i = 0;i < n;i++){
            if(dp[mask][i] == INT_MAX) continue;
            for(int j = 0;j < n;j++){
                if(mask >> j & 1) continue;//访问过则跳过
                int newMask = mask|(1<<j);
                if(dp[newMask][j] > dp[mask][i] + village[i][j]){
                    dp[newMask][j] = dp[mask][i] + village[i][j];
                }
            }
        }
    }
    //返回起点
    //此处不能直接dp[total-1][i]-->显然已经访问过，不会被重新赋值(不可达)
    int ans = INT_MAX;
    for(int i = 0;i < n;i++){
        if(dp[total-1][i] == INT_MAX) continue;
        ans = min(ans,dp[total-1][i]+village[i][0]);
    }
    cout << ans;
}
