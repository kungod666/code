/*# P1884 [USACO12FEB] Overplanting S

## 题目描述

在一个笛卡尔平面坐标系里（则 $X$ 轴向右是正方向，$Y$ 轴向上是正方向），有 $N\ (1 \le N \le 1000)$ 个矩形，第 $i$ 个矩形的左上角坐标是 $(x_1,y_1)$，右下角坐标是 $(x_2,y_2)$。问这 $N$ 个矩形所覆盖的面积是多少？

注意：被重复覆盖的区域的面积只算一次。

## 输入格式

第一行，一个整数 $N\ (1 \le N \le 1000)$。

接下来有 $N$ 行，每行描述一个矩形的信息，分别是矩形的 $x_1,y_1,x_2,y_2(-10^8 \le x_1,y_1,x_2,y_2 \le 10^8)$。

## 输出格式

一个整数，被 $N$ 个矩形覆盖的区域的面积。

## 输入输出样例 #1

### 输入 #1

```
2
0 5 4 1
2 4 6 2

```

### 输出 #1

```
20
```*/

//扫描线算法


/*扫描线算法，就是移动x，去求x区间内覆盖的矩形面积，整个过程
核心是cover数组的维护来判断是否这个y区间内还存在矩形*/
//对于y（10^8)，会用到离散化，但本题核心还是扫描线算法
//因为数据量温和原因(N <= 1000)，所以虽然是区间查询和修改，但用不着线段树
//如果想深化对扫描线算法理解，可以去做P1856
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll N;
typedef struct Side{
    ll x;
    ll y1;
    ll y2;
    ll d;//1为左边界，-1为右边界
}Side;
bool cmp(const Side& a,const Side& b){
    if(a.x != b.x) return a.x < b.x;
    return a.d > b.d;
}
int main(){
    cin >> N;
    Side side[2007];
    vector<ll> map;
    for(int i = 0;i < N;i++){
        ll x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        side[2*i].x = x1;
        side[2*i+1].x = x2;
        side[2*i].y1 = y1;
        side[2*i].y2 = y2;
        side[2*i+1].y1 = y1;
        side[2*i+1].y2 = y2;
        side[2*i].d = 1;
        side[2*i+1].d = -1;
        map.push_back(y1);
        map.push_back(y2);
    }
    //索引:0~2*N-1
    vector<ll> cover(2007);//区间个数
    sort(side,side+(2*N),cmp);
    sort(map.begin(),map.end());
    auto m = unique(map.begin(),map.end());
    map.erase(m,map.end());
    int M  = map.size();//y坐标个数
    ll prev_x = side[0].x;
    ll ans = 0;
    for(int i = 0;i < 2*N;i++){
        Side& tmp = side[i];
        ll dx = tmp.x - prev_x;
        ll len = 0;
        for(int j = 0;j < M-1;j++){
            if(cover[j] > 0){
                len += map[j+1] -map[j];
            }
        }
        ans += len*dx;
        ll y1_idx = lower_bound(map.begin(),map.end(),tmp.y1)-map.begin();
        ll y2_idx = lower_bound(map.begin(),map.end(),tmp.y2)-map.begin();
        for(int j = y2_idx;j < y1_idx;j++){
            cover[j] += tmp.d;
        }
        prev_x = tmp.x;
    }
    cout << ans;
}