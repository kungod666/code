#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
int main(){
    ll n,m,k;
    cin >> n >> m >> k;
    vector<ll> cost(n);
    cost[0] = 0;
    for(int i = 1;i < n;i++){
        cin >> cost[i];
    }
    vector<ll> sum_cost(n);//前缀和优化
    vector<ll> mineral(n);
    for(int i = 0;i < n;i++){
        cin >> mineral[i];
    }
    sum_cost[0] = cost[0];
    for(int i = 1;i < n;i++){
        sum_cost[i] = sum_cost[i-1] + cost[i];
    }
    priority_queue<ll,vector<ll>,greater<ll>> mines;
    //小顶堆
    priority_queue<ll> max_mineral;
    int sum = 0;
    //状态是在i点结束
    for(int i = 0;i < n;i++){
        ll money = m - sum_cost[i];
        if(money > 0){
            sum += mineral[i];
            mines.push(mineral[i]);
            while(mines.size() > k){
                sum -= mines.top();
                mines.pop();
            }
            ll ans = money >= sum ? sum : money;
            max_mineral.push(ans);
        }
        else break;
    }
    cout << max_mineral.top();
}