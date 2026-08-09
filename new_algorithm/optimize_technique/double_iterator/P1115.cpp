//前缀和 + 最小前缀和优化
/*区间和最大/最小
→ 先写成前缀和相减
→ 固定一个端点
→ 维护另一个端点对应的最优前缀值*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
int main(){
    cin >> n;
    vector<int> num(n+1);
    vector<int> sum(n+1);
    for(int i = 1;i <= n;i++){
        cin >> num[i];
        sum[i] = sum[i-1]+num[i];
    }
    ll ans = -100000;
    vector<int> rec(n+1);
    rec[1] = 1;
    for(int i = 2;i <= n;i++){
        if(sum[rec[i-1]] - num [rec[i-1]]> sum[i] - num[i]){
            rec[i] = i;
        }
        else{
            rec[i] = rec[i-1];
        }
    }
    for(int i = 1;i <= n;i++){
        ans = max(ans,(ll)sum[i] - sum[rec[i]] + num[rec[i]]);
    }
    cout << ans;
}