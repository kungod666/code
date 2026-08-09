/*# P1775 石子合并（弱化版）

## 题目描述

设有 $N(N \le 300)$ 堆石子排成一排，其编号为 $1,2,3,\cdots,N$。每堆石子有一定的质量 $m_i\ (m_i \le 1000)$。现在要将这 $N$ 堆石子合并成为一堆。每次只能合并相邻的两堆，合并的代价为这两堆石子的质量之和，合并后与这两堆石子相邻的石子将和新堆相邻。合并时由于选择的顺序不同，合并的总代价也不相同。试找出一种合理的方法，使总的代价最小，并输出最小代价。

## 输入格式

第一行，一个整数 $N$。

第二行，$N$ 个整数 $m_i$。

## 输出格式

输出文件仅一个整数，也就是最小代价。

## 输入输出样例 #1

### 输入 #1

```
4
2 5 3 1
```

### 输出 #1

```
22
```*/
//区间dp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n;
ll rocks[310],dp[310][310],sum[310],len;
//dp[i][j]表示将第 i 堆到第 j 堆石子合并成一堆的最小代价
int main(){
    cin >> n;
    memset(dp,0x3f,sizeof(dp));
    //因为求最小值，所以初始化一个很大的数(memset特性:0x3f初始化为无穷大)
    //为啥不用INT_MAX?----怕爆int
    for(int i = 1;i <= n;i++){
        cin >> rocks[i];
        sum[i] = sum[i-1] + rocks[i];
        dp[i][i] = 0;
    }
    for(int len = 2;len <= n;len++){
        for(int i = 1;i <= n - len + 1;i++){
            int j = i+len-1;//确定终点
            for(int k = i;k < j;k++){//确定分割点
                dp[i][j] = min(dp[i][j],dp[i][k]+dp[k+1][j]+sum[j] - sum[i-1]);
            }
        }
    }
    cout << dp[1][n];
}