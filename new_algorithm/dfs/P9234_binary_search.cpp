/*# P9234 [蓝桥杯 2023 省 A] 买瓜

## 题目描述

小蓝正在一个瓜摊上买瓜。瓜摊上共有 $n$ 个瓜，每个瓜的重量为 $A_i$。小蓝刀功了得，他可以把任何瓜劈成完全等重的两份，不过每个瓜只能劈一刀。

小蓝希望买到的瓜的重量的和恰好为 $m$。

请问小蓝至少要劈多少个瓜才能买到重量恰好为 $m$ 的瓜。如果无论怎样小蓝都无法得到总重恰好为 $m$ 的瓜，请输出 $-1$。

## 输入格式

输入的第一行包含两个整数 $n,m$，用一个空格分隔，分别表示瓜的个数和小蓝想买到的瓜的总重量。

第二行包含 $n$ 个整数 $A_i$，相邻整数之间使用一个空格分隔，分别表示每个瓜的重量。

## 输出格式

输出一行包含一个整数表示答案。

## 输入输出样例 #1

### 输入 #1

```
3 10
1 3 13
```

### 输出 #1

```
2
```

## 说明/提示

#### 【评测用例规模与约定】

对于 $20 \%$ 的评测用例，$n \leq 10$;

对于 $60 \%$ 的评测用例，$n \leq 20$;

对于所有评测用例，$1 \leq n \leq 30$，$1 \leq A_i \leq 10^9$，$1 \leq m \leq 10^9$。*/

/*算法思路：
dfs是常规思路（因为m是目标值，如果是求最大这种就dp了），但是n有可能为30，而dfs到每一个瓜都会有三种选择:拿这个瓜，切开后拿一半
不拿这个瓜；这样的话O最大是 3^30，包超1e8，所以我们应该调整算法
考虑适当剪枝？当然可以，我们可以根据切刀数大于最优解否，当前sum重量大于m否，
当前遍历大于数量否剪枝。但这些还是不足
于是我们考虑折半搜索
(这里还有个小巧思是为了避免double的精度问题，我们将m *= 2，
这样在考虑切西瓜时就不用担心小数产生)*/
#include <iostream>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;
ll walon[35];
int n,m;
ll ans = INT_MAX;
map<ll,ll> cnts;//cnts[i] = k表示得到i重的瓜需要切几个
void dfs1(ll pos,ll weight,ll times){
    if(weight == m){
        ans = ans > times? times : ans;
        return;
    }
    if(weight > m) return;
    if(pos > n/2+1) return;
    if(cnts.count(weight) && cnts[weight] < times) return;
    cnts[weight] = times;
    dfs1(pos+1,weight,times);
    dfs1(pos+1,weight+2*walon[pos],times);
    dfs1(pos+1,weight+walon[pos],times+1);
}
void dfs2(ll pos,ll weight,ll times){
    if(cnts.count(m-weight)){
        ans = ans > (cnts[m-weight]+times)?(cnts[m-weight]+times):ans;
        return;
    }
    if(pos > n+1) return;
    if(weight > m) return;
    dfs2(pos+1,weight,times);
    dfs2(pos+1,weight+2*walon[pos],times);
    dfs2(pos+1,weight+walon[pos],times+1);
}
int main(){
    cin >> n >> m;
    m *= 2;
    fill(walon,walon+35,INT_MAX);
    //在algorithm头文件
    walon[0] = 0;
    for(int i = 1;i <= n;i++){
        cin >> walon[i];
    }
    sort(walon+1,walon+n+1);
    //预处理优化，便于后续剪枝
    cnts[0] = 0;
    dfs1(1,0,0);
    dfs2(n/2+1,0,0);
    if(ans == INT_MAX) cout << -1;
    else cout << ans;
}