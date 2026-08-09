//#include <bits/stdc++.h>
/*# P15968 电梯接客
## 题目描述
在小 C 居住的星球上，有一座高 $Y$ 层的摩天大楼。
现在，这座摩天大楼的第 $Y$ 层（顶层）将要举行一场重要的会议。总共有 $N$ 个请求，第 $i$ 个请求为：
- 第 $F_i$ 层有 $A_i$ 个人需要参加会议。
电梯初始停在第 $X$ 层，且每上一层或下一层都需要 $1$ 单位时间。电梯可以在任意楼层停靠，且开门、关门、上电梯、下电梯的时间均忽略不计。
另外，电梯有载重，即同一时间内电梯内部人数不能超过 $W$ 人。小 C 想知道，最少需要多少单位时间，才能让电梯将所有需要参加会议的人都接到第 $Y$ 层。
## 输入格式
第一行，四个整数 $N,X,Y,W$。
接下来 $N$ 行，每行两个整数 $F_i,A_i$。
## 输出格式
一个整数，表示答案。
## 输入输出样例 #1
### 输入 #1
```
3 5 10 4
2 3
7 10
9 2
```
### 输出 #1

```
29
```
## 说明/提示
**【样例解释】**
样例中，电梯先到 $2$ 层接 $3$ 人到 $10$ 层，再到 $7$ 层接 $2$ 次 $4$ 人到 $10$ 层，最后到 $7$ 层接 $2$ 人，带上 $9$ 层的 $2$ 人到 $10$ 层，总代价为 $3+8+3+3+3+3+3+3=29$。
**【数据范围】**
对于 $30\%$ 的评测用例，保证 $1 \le N,X,Y,F_i,A_i,W \le 10^3$。
另有 $10\%$ 的评测用例，保证 $A_i=1$。
另有 $10\%$ 的评测用例，保证 $A_i$ 是 $W$ 的倍数。
对于 $100\%$ 的评测用例，保证 $1 \le N,X,Y,F_i,A_i \le 10^6$，$1 \le W \le 10^{12}$，$X,F_i \le Y$，所有的 $F_i$ 互不相同。*/
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>
using namespace std;
int main(){
    long long N,X,Y,W;
    cin >> N >> X >> Y >> W;
    vector<pair<long,long>> orders(N);
    pair<long,long> temp;
    for(int i = 0;i < N;i++){
        cin >> temp.first >> temp.second;
        orders[i] = temp;
    }
    sort(orders.begin(),orders.end());
    long long ans = 0;
    ans += abs(X-orders[0].first);
    for(int i = 0;i < N;i++){
        ans += (orders[i].second / W)*(Y-orders[i].first)*2LL;
        if(orders[i].second % W){
            if(i != N-1){
                orders[i+1].second += (orders[i].second % W);
                ans += (orders[i+1].first - orders[i].first);
            }
            else{
                ans += (Y - orders[i].first);
            }
        }
        else{
            ans -= (Y-orders[i].first);
            if(i != N-1) ans += (Y-orders[i+1].first);
        }
    }
    cout << ans;
}