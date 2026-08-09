/*# P16227 [蓝桥杯 2026 省 A] 切割木材

## 题目描述

角落里，一台老旧的自动分装机正发出沉闷的轰鸣声。

小蓝站在流水线旁，准备将一批木材送入分装机。机器的挡板间距 $L$ 是唯一可调参数，任何长度超过 $L$ 的木段都会导致传送带卡死。显然，挡板间距越小，单位时间内的输送密度就越高。因此，小蓝希望将这个挡板间距 $L$ 设定得尽可能小。

眼前有 $N$ 根原始木材，第 $i$ 根的长度为 $A_i$。小蓝可以对这些木材进行切割以满足长度要求，但由于锯片磨损，他全程最多只能进行 $K$ 次切割。具体的切割规则如下：

1. 每次切割可以将一根木材切割为两段。
2. 分割后，新产生的两段木材的长度必须为正整数，且长度之和等于原木材的长度。

现在，请你为小蓝找出这个最小可行的挡板间距 $L$，使得在总切割次数不超过 $K$ 的前提下，切割后所有木段的最大长度不超过 $L$。

## 输入格式

第一行包含两个整数 $N$ 和 $K$，分别表示原始木材的数量和最大切割次数。

第二行包含 $N$ 个整数 $A_1, A_2, \ldots, A_N$，表示每根原始木材的长度。

## 输出格式

输出一个整数，表示最小可行的挡板间距 $L$。

## 输入输出样例 #1

### 输入 #1

```
1 1
5
```

### 输出 #1

```
3
```

## 输入输出样例 #2

### 输入 #2

```
2 3
9 6
```

### 输出 #2

```
3
```

## 说明/提示

### 【评测用例规模与约定】

对于 $10\%$ 的评测用例，$1 \le N \le 100$，$0 \le K \le 3$，$1 \le A_i \le 10^3$。

对于 $50\%$ 的评测用例，$1 \le N \le 10^3$，$0 \le K \le 10^5$，$1 \le A_i \le 10^5$。

对于 $100\%$ 的评测用例，$1 \le N \le 10^6$，$0 \le K \le 10^9$，$1 \le A_i \le 10^9$。*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int n,k;
typedef long long ll;
vector<ll> woods;
ll max_num = -1;
ll cuts(ll len){
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(woods[i] <= len) continue;
        cnt += ((woods[i]+len-1)/len) - 1;
        if(cnt > k) break;
    }
    return cnt;
}
ll solve(){
    ll l = 1;
    ll r = max_num;
    ll ans = max_num;
    while(l <= r){
        ll mid = (l+r)>>1;
        if(cuts(mid) <= k){
            ans = mid;
            r = mid-1;
        }
        else{
            l = mid+1;
        }
    }
    return ans;
}
int main(){
    cin >> n >> k;
    //显然，最大值最小题型，我们可以从L入手
    //因为L有确定范围(1~amax);
    vector<ll> tmp(n+1);
    //1~n
    woods = tmp;
    for(int i = 1;i <= n;i++){
        cin >> woods[i];
        if(woods[i] > max_num) max_num = woods[i];
    }
    cout << solve();
}