/*# P1443 马的遍历
## 题目描述
有一个 $n \times m$ 的棋盘，在某个点 $(x, y)$ 上有一个马，
要求你计算出马到达棋盘上任意一个点最少要走几步。
## 输入格式
输入只有一行四个整数，分别为 $n, m, x, y$。
## 输出格式
一个 $n \times m$ 的矩阵，
代表马到达某个点最少要走几步（不能到达则输出 $-1$）。
## 输入输出样例 #1
### 输入 #1
```
3 3 1 1
```
### 输出 #1
```
0 3 2    
3 -1 1    
2 1 4    
``
## 说明/提示
### 数据规模与约定
对于全部的测试点，保证 $1 \leq x \leq n \leq 400$，$1 \leq y \leq m \leq 400$。
2022 年 8 月之后，本题去除了对输出保留场宽的要求。为了与之兼容，本题的输出以空格或者合理的场宽分割每个整数都将判作正确。*/
#include <iostream>
#include <iterator>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
vector<vector<int>> chess;
vector<vector<int>> book;
int n,m,x,y;
int step = 0;
queue<pair<int,int>> point;
void bfs(){
    pair<int,int> rec;
    int count;
    pair<int,int> mp;
    while(!(point.empty())){
        count = point.size();
        while(count-- > 0){
            rec = point.front();
            point.pop();
            chess[rec.first][rec.second] = step;
            
            if(rec.first-1 >= 1 && rec.first <= n &&
            rec.second -2 >= 1 && rec.second <= m && !book[rec.first-1][rec.second-2] ){
                mp.first = rec.first-1;
                mp.second = rec.second -2;
                book[mp.first][mp.second] = 1;
                //md,bfs一定要记得入队就book，要不然出队book==MLE
                point.push(mp);
            }
            if(rec.first >= 1 && rec.first+1 <= n &&
            rec.second -2 >= 1 && rec.second <= m && !book[rec.first+1][rec.second-2] ){
                mp.first = rec.first+1;
                mp.second = rec.second -2;
                book[mp.first][mp.second] = 1;
                point.push(mp);
            }
            if(rec.first >= 1 && rec.first+1 <= n &&
            rec.second  >= 1 && rec.second+2 <= m && !book[rec.first+1][rec.second+2] ){
    
                mp.first = rec.first+1;
                mp.second = rec.second +2;
                book[mp.first][mp.second] = 1;
                point.push(mp);
            }
            if(rec.first -1 >= 1 && rec.first <= n &&
            rec.second  >= 1 && rec.second+2 <= m && !book[rec.first-1][rec.second+2] ){
                
                mp.first = rec.first-1;
                mp.second = rec.second +2;
                book[mp.first][mp.second] = 1;
                point.push(mp);
            }
            if(rec.first-2 >= 1 && rec.first <= n &&
            rec.second -1 >= 1 && rec.second <= m && !book[rec.first-2][rec.second-1] ){
             
                mp.first = rec.first-2;
                mp.second = rec.second -1;
                book[mp.first][mp.second] = 1;
                point.push(mp);
            }
            if(rec.first-2 >= 1 && rec.first <= n &&
            rec.second >= 1 && rec.second+1 <= m && !book[rec.first-2][rec.second+1] ){
               
                mp.first = rec.first-2;
                mp.second = rec.second + 1;
                book[mp.first][mp.second] = 1;
                point.push(mp);
            }
            if(rec.first >= 1 && rec.first+2 <= n &&
            rec.second >= 1 && rec.second+1 <= m && !book[rec.first+2][rec.second+1] ){
               
                mp.first = rec.first+2;
                mp.second = rec.second + 1;
                book[mp.first][mp.second] = 1;
                point.push(mp);
            }
            if(rec.first >= 1 && rec.first+2 <= n &&
            rec.second-1 >= 1 && rec.second <= m && !book[rec.first+2][rec.second-1] ){
               
                mp.first = rec.first+2;
                mp.second = rec.second - 1;
                book[mp.first][mp.second] = 1;
                point.push(mp);
            }
        }
        step++;
    }

}
int main(){
    cin >> n >> m >> x >> y;
    vector<vector<int>> temp(n+1,vector<int>(m+1));
    chess = temp;
    book = temp;
    pair<int,int> jb;
    book[x][y] = 1;
    jb.first = x;
    jb.second = y;
    point.push(jb);
    bfs();
    for(int i = 1;i <=n;i++){
        for(int j = 1;j <= m;j++){
            if((i != x || j != y)&&(chess[i][j] == 0) ){
                cout << -1 << " ";
            }
            else cout << chess[i][j] << " ";
        }
        cout << "\n";
    }
}