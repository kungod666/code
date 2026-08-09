/*# P1434 [SHOI2002] 滑雪

## 题目描述

Michael 喜欢滑雪。这并不奇怪，因为滑雪的确很刺激。可是为了获得速度，滑的区域必须向下倾斜，而且当你滑到坡底，你不得不再次走上坡或者等待升降机来载你。Michael 想知道在一个区域中最长的滑坡。区域由一个二维数组给出。数组的每个数字代表点的高度。下面是一个例子：
```plain
1   2   3   4   5
16  17  18  19  6
15  24  25  20  7
14  23  22  21  8
13  12  11  10  9
```
一个人可以从某个点滑向上下左右相邻四个点之一，当且仅当高度会减小。在上面的例子中，一条可行的滑坡为 $24-17-16-1$（从 $24$ 开始，在 $1$ 结束）。当然    $25$－$24$－$23$－$\ldots$－$3$－$2$－$1$ 更长。事实上，这是最长的一条。

## 输入格式

输入的第一行为表示区域的二维数组的行数 $R$ 和列数 $C$。下面是 $R$ 行，每行有 $C$ 个数，代表高度（两个数字之间用 $1$ 个空格间隔）。

## 输出格式

输出区域中最长滑坡的长度。

## 输入输出样例 #1

### 输入 #1

```
5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9

```

### 输出 #1

```
25
```

## 说明/提示

对于 $100\%$ 的数据，$1\leq R,C\leq 100$。*/

/*算法关键思想：dfs搜索，dfs内部状态转移*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int r,c;
vector<vector<int>> area;
vector<vector<int>> s;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int dfs(int x,int y){
    if(s[x][y]) return s[x][y];//记忆化搜索
    s[x][y] = 1;//以(x,y)作为滑雪起点，长度至少为1
    for(int i = 0;i < 4;i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        int route;
        if(new_x >= 1 && new_x <= r && 
            new_y >= 1 && new_y <=c && area[new_x][new_y] < area[x][y]){
            route = dfs(new_x,new_y)+1;
            s[x][y] = max(s[x][y],route);
        }
    }
    return s[x][y];
}
int main(){
    cin >> r >> c;
    vector<vector<int>> temp(r+1,vector<int>(c+1));
    area = temp;
    s = temp;
    for(int i = 1;i <= r;i++){
        for(int j = 1;j <= c;j++){
            cin >> area[i][j];
        }
    }
    int ans = 0;
    for(int i = 1;i <= r;i++){
        for(int j = 1;j <= c;j++){
            ans = max(dfs(i,j),ans);
        }
    }
    cout << ans << "\n";
}