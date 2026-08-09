#include <iostream>
#include <vector>
using namespace std;
long long t,m;
vector<long long> cost;
vector<long long> value;
int main(){
    cin >> t >> m;
    vector<long long> tmp(m);
    cost = tmp;
    value = tmp;
    for(int i = 1;i <= m;i++){
        cin >> cost[i-1] >> value[i-1];
    }
    vector<long long> dp(t+1,-1);
    //0->t
    dp[0] = 0;
    //外层遍历物品，内层遍历状态
    for(int i = 0;i < m;i++){
        for(int j = t;j >= 0;j--){
            //内层从上至下，避免同一物品反复使用
            if(j - cost[i] < 0 || dp[j-cost[i]] == -1) continue;
        if(dp[j-cost[i]] + value[i] > dp[j]){
            dp[j] =dp[j-cost[i]] + value[i];
        }
        }
    }
    long long max = -1;
    for(int i = 0;i <= t;i++){
        if(dp[i] > max) max = dp[i];
    }
    cout << max << "\n";

    return 0;
}