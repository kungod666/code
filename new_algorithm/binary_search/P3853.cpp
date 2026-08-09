/*# P3853 [TJOI2007] 路标设置

## 题目背景

B 市和 T 市之间有一条长长的高速公路，这条公路的某些地方设有路标，但是大家都感觉路标设得太少了，相邻两个路标之间往往隔着相当长的一段距离。为了便于研究这个问题，我们把公路上相邻路标的最大距离定义为该公路的“空旷指数”。

## 题目描述

现在政府决定在公路上增设一些路标，使得公路的“空旷指数”最小。他们请求你设计一个程序计算能达到的最小值是多少。请注意，公路的起点和终点保证已设有路标，公路的长度为整数，并且原有路标和新设路标都必须距起点整数个单位距离。

## 输入格式

第 $1$ 行包括三个数 $L,N,K$，分别表示公路的长度，原有路标的数量，以及最多可增设的路标数量。


第 $2$ 行包括递增排列的 $N$ 个整数，分别表示原有的 $N$ 个路标的位置。路标的位置用距起点的距离表示，且一定位于区间 $[0,L]$ 内。

## 输出格式

输出 $1$ 行，包含一个整数，表示增设路标后能达到的最小“空旷指数”值。

## 输入输出样例 #1

### 输入 #1

```
101 2 1
0 101
```

### 输出 #1

```
51
```

## 说明/提示

公路原来只在起点和终点处有两个路标，现在允许新增一个路标，应该把新路标设在距起点 $50$ 或 $51$ 个单位距离处，这样能达到最小的空旷指数 $51$。

$50\%$ 的数据中，$2 \leq N \leq 100$，$0 \leq K \leq 100$。

$100\%$ 的数据中，$2 \leq N \leq 100000$, $0 \leq K \leq100000$。

$100\%$ 的数据中，$0 < L \leq 10000000$。*/
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
ll l,n,k;
ll ans = LONG_LONG_MAX;
ll max_dis;
//这里的max_dis不能取stones中最大值---->最终可能L远大于stones中值
//取L最保险!!!(反正o(nlogL也不会超时))
vector<ll> stones;
void solve(){
    ll left = 1;
    ll right = l;
    ll mid;
    while(left <= right){
        mid = (left+right)>>1;
        ll last = 0;
        ll count = 0;
        for(int i = 1;i <= n;i++){
            if(stones[i] - last > mid){
                count += (stones[i] - last-1)/mid;
                //不可写作(stones[i] - last)/mid;否则多加数量
            }
            last = stones[i];
        }
        if(l - last > mid) count += (l-last-1)/mid;
        if(count <= k){
            ans = min(mid,ans);
            right = mid-1;
        }
        else if(count > k){
            left = mid+1;
        }
    }
}
int main(){
    cin >> l >> n >> k;
    max_dis = l;
    stones.resize(n+1);
    for(int i = 1;i <= n;i++){
        cin >> stones[i];
    }
    if(k != 0){
        solve();
        cout << ans;
    }
    else{
        ll last = 0;
        ll empty_num = -1;
        for(int i = 1;i <= n;i++){
            empty_num = max(stones[i]-last,empty_num);
        }
        empty_num = max(empty_num,l-stones[n]);
        cout << empty_num;
    }
}