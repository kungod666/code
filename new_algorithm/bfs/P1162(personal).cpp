/*# P1162 填涂颜色

## 题目描述

由数字 $0$ 组成的方阵中，有一任意形状的由数字 $1$ 构成的闭合圈。现要求把闭合圈内的所有空间都填写成 $2$。例如：$6\times 6$ 的方阵（$n=6$），涂色前和涂色后的方阵如下：

如果从某个 $0$ 出发，只向上下左右 $4$ 个方向移动且仅经过其他 $0$ 的情况下，无法到达方阵的边界，就认为这个 $0$ **在闭合圈内**。闭合圈不一定是环形的，可以是任意形状，但保证**闭合圈内**的 $0$ 是连通的（两两之间可以相互到达）。

```plain
0 0 0 0 0 0
0 0 0 1 1 1
0 1 1 0 0 1
1 1 0 0 0 1
1 0 0 1 0 1
1 1 1 1 1 1
```
```plain
0 0 0 0 0 0
0 0 0 1 1 1
0 1 1 2 2 1
1 1 2 2 2 1
1 2 2 1 2 1
1 1 1 1 1 1
```

## 输入格式

每组测试数据第一行一个整数 $n(1 \le n \le 30)$。

接下来 $n$ 行，由 $0$ 和 $1$ 组成的 $n \times n$ 的方阵。

方阵内只有一个闭合圈，圈内至少有一个 $0$。

## 输出格式

已经填好数字 $2$ 的完整方阵。

## 输入输出样例 #1

### 输入 #1

```
6
0 0 0 0 0 0
0 0 1 1 1 1
0 1 1 0 0 1
1 1 0 0 0 1
1 0 0 0 0 1
1 1 1 1 1 1

```

### 输出 #1

```
0 0 0 0 0 0
0 0 1 1 1 1
0 1 1 2 2 1
1 1 2 2 2 1
1 2 2 2 2 1
1 1 1 1 1 1

```

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 30$。*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
int n;
vector<vector<int>> graph;
vector<vector<int>> res;
vector<vector<int>> avoid;
int flag = 0;
void bfs(int x,int y){
    vector<vector<int>> book(n+1,vector<int>(n+1));
    queue<pair<int,int>> point;
    point.emplace(x,y);
    book[x][y] = 1;
    int pivot = 0;
    while(!point.empty()){
        int num = point.size();
        pair<int,int> rec;
        while(num-->0){
            rec = point.front();
            point.pop();
            if(rec.first + 1 == n && graph[rec.first+1][rec.second] == 0&&!pivot){
                pivot = 1;
            }
            else if(rec.first -1 == 1 && graph[rec.first-1][rec.second] == 0&&!pivot){
                pivot = 1;
            }
            else if(rec.second -1 == 1 && graph[rec.first][rec.second-1] == 0&&!pivot){
                pivot = 1;
            }
            else if(rec.second +1 == n && graph[rec.first][rec.second+1] == 0&&!pivot){
                pivot = 1;
            }

            if(rec.first+1 <= n && rec.first >=1
            &&rec.second >=1 && rec.second <=n && !graph[rec.first+1][rec.second]&& !book[rec.first+1][rec.second]
            ){
                book[rec.first+1][rec.second] = 1;
                point.emplace(rec.first+1,rec.second);
            }
            if(rec.first <= n && rec.first-1 >=1
            &&rec.second >=1 && rec.second <=n && !book[rec.first-1][rec.second]
            && !graph[rec.first-1][rec.second]
            ){
                book[rec.first-1][rec.second] = 1;
                point.emplace(rec.first-1,rec.second);
            }
            if(rec.first <= n && rec.first >=1
            &&rec.second >=1 && rec.second+1 <=n && !book[rec.first][rec.second+1]
            && !graph[rec.first][rec.second+1]
            ){
                book[rec.first][rec.second+1] = 1;
                point.emplace(rec.first,rec.second+1);
            }
            if(rec.first <= n && rec.first >=1
            &&rec.second >=1 && rec.second-1 <=n && !book[rec.first][rec.second-1]
            && !graph[rec.first][rec.second-1]
            ){
                book[rec.first][rec.second-1] = 1;
                point.emplace(rec.first,rec.second-1);
            }
        }
    }
    if(pivot){
        avoid = book;
        return;
    }
    else{
        flag = 1;
        res = book;
    }
}
int main(){
    cin >> n;
    int rece;
    vector<vector<int>> temp(n+1,vector<int>(n+1));
    graph = temp;
    res = temp;
    avoid = temp;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cin >> rece;
            if(rece == 1){
                graph[i][j] = 1;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(flag) break;
            if(!graph[i][j]&&!avoid[i][j]){
                bfs(i,j);
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(res[i][j] == 1){
                graph[i][j] = 2;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
}