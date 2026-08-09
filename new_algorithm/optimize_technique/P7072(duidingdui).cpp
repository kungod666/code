/*# P7072 [CSP-J 2020] 直播获奖

## 题目描述

NOI2130 即将举行。为了增加观赏性，CCF 决定逐一评出每个选手的成绩，并直播即时的获奖分数线。本次竞赛的获奖率为 $w\%$，即当前排名前 $w\%$ 的选手的最低成绩就是即时的分数线。

更具体地，若当前已评出了 $p$ 个选手的成绩，则当前计划获奖人数为 $\max(1, \lfloor p \times w \%\rfloor)$，其中 $w$ 是获奖百分比，$\lfloor x \rfloor$ 表示对 $x$ 向下取整，$\max(x,y)$ 表示 $x$ 和 $y$ 中较大的数。如有选手成绩相同，则所有成绩并列的选手都能获奖，因此实际获奖人数可能比计划中多。

作为评测组的技术人员，请你帮 CCF 写一个直播程序。

## 输入格式

第一行有两个整数 $n, w$。分别代表选手总数与获奖率。  
第二行有 $n$ 个整数，依次代表逐一评出的选手成绩。

## 输出格式

只有一行，包含 $n$ 个非负整数，依次代表选手成绩逐一评出后，即时的获奖分数线。相邻两个整数间用一个空格分隔。

## 输入输出样例 #1

### 输入 #1

```
10 60
200 300 400 500 600 600 0 300 200 100

```

### 输出 #1

```
200 300 400 400 400 500 400 400 300 300
```

## 输入输出样例 #2

### 输入 #2

```
10 30
100 100 600 100 100 100 100 100 100 100
```

### 输出 #2

```
100 100 600 600 600 600 100 100 100 100
```

## 说明/提示

### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/l453vhow.png)

---
### 数据规模与约定

各测试点的 $n$ 如下表：

| 测试点编号 | $n=$ |
| :--: | :--: |
| $1 \sim 3$ | $10$ |
| $4 \sim 6$ | $500$ |
| $7 \sim 10$ | $2000$ |
| $11 \sim 17$ | $10^4$ |
| $18 \sim 20$ | $10^5$ |


对于所有测试点，每个选手的成绩均为不超过 10^5 的非负整数，获奖百分比 $w$ 是一个正整数且 $1 \le w \le 99$。

---
### 提示

在计算计划获奖人数时，如用浮点类型的变量（如 C/C++ 中的 `float` 、 `double`，Pascal 中的 `real` 、 `double` 、 `extended` 等）存储获奖比例 $w\%$，则计算 $5 \times 60\%$ 时的结果可能为 $3.000001$，也可能为 $2.999999$，向下取整后的结果不确定。因此，建议仅使用整型变量，以计算出准确值。*/


//由于成绩范围很大，桶计数不可取，故我们用对顶堆
/*对顶堆:
在数据多且数据范围很大时要维护
动态区间内第k大的元素*/

/*规则:
1.始终保持big堆中个数为k
2。始终保持small堆中各元素小于big堆最小元素*/
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int n, w;

int main() {
    cin >> n >> w;

    priority_queue<int> small;
    priority_queue<int, vector<int>, greater<int>> big;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        int k = max(1, i * w / 100);

        if (big.empty() || x >= big.top()) {
            big.push(x);
        } else {
            small.push(x);
        }

        while ((int)big.size() > k) {
            small.push(big.top());
            big.pop();
        }

        while ((int)big.size() < k) {
            big.push(small.top());
            small.pop();
        }

        cout << big.top() << " ";
    }

    return 0;
}