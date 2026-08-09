/*# P2367 语文成绩

## 题目背景

语文考试结束了，成绩还是一如既往地有问题。

## 题目描述

语文老师总是写错成绩，所以当她修改成绩的时候，总是累得不行。她总是要一遍遍地给某些同学增加分数，又要注意最低分是多少。你能帮帮她吗？

## 输入格式

第一行有两个整数 $n$，$p$，代表学生数与增加分数的次数。

第二行有 $n$ 个数，$a_1 \sim a_n$，代表各个学生的初始成绩。

接下来 $p$ 行，每行有三个数，$x$，$y$，$z$，代表给第 $x$ 个到第 $y$ 个学生每人增加 $z$ 分。

## 输出格式

输出仅一行，代表更改分数后，全班的最低分。

## 输入输出样例 #1

### 输入 #1

```
3 2
1 1 1
1 2 1
2 3 1
```

### 输出 #1

```
2

```

## 说明/提示

对于 $40\%$ 的数据，有 $n \le 10^3$。

对于 $60\%$ 的数据，有 $n \le 10^4$。

对于 $80\%$ 的数据，有 $n \le 10^5$。

对于 $100\%$ 的数据，有 $n \le 5\times 10^6$，$p \le n$，学生初始成绩 $ \le 100$，$z \le 100$。*/
//差分
#include <climits>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n,p;
vector<ll> scores;
vector<ll> d;
//差分数组的定义： d[i]=scores[i]-scores[i-1]
//差分数组核心用途：高效处理对一个数组的“区间增删”操作
//差分数组是“离线”算法，必须先记录下所有修改，最后一次性还原。如果流程是改一次就要立刻知道结果，差分就不适用了。
//(当同时涉及区间增删与查询时，需要用到线段树(在线操作))
int main(){
    cin >> n >> p;
    scores.resize(n+1);
    d.resize(n+1);
    for(int i = 1;i <= n;i++){
        cin >> scores[i];
        d[i] = scores[i] - scores[i-1];
    }
    for(int i = 1;i <= p;i++){
        ll x,y,z;
        cin >> x >> y >> z;
        d[x] += z;
        if(y != n)d[y+1] -= z;
    }
    for(int i = 1;i <= n;i++){
        scores[i] = d[i]+scores[i-1];
    }
    ll ans = LLONG_MAX;
    for(int i = 1;i <= n;i++){
        ans = min(ans,scores[i]);
    }
    cout << ans;
}