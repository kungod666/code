/*给定一个 N×M 方格的迷宫，迷宫里有 T 处障碍，障碍处不可通过。
在迷宫中移动有上下左右四种方式，每次只能移动一个方格。数据保证起点上没有障碍。
给定起点坐标和终点坐标，每个方格最多经过一次，
问有多少种从起点坐标到终点坐标的方案。*/
#include <iostream>
#include <vector>
using namespace std;
int  N,M,T,sx,sy,fx,fy;
int ans = 0;
vector<vector<int>> puzzle;
void dfs(int x,int y){
    if(x > N || y > M
    || x < 1 || y < 1 || puzzle[x][y] == 1) return;
    if(x == fx && y == fy){
        ans++;
        return;
    }
    puzzle[x][y] = 1;
    dfs(x+1,y);
    dfs(x-1,y);
    dfs(x,y+1);
    dfs(x,y-1);
    puzzle[x][y] = 0;
}
int main(){
    cin >> N >> M >> T;
    cin >> sx >> sy >> fx >> fy;
    int tp_x,tp_y;
    vector<vector<int>> temp(N+1,vector<int>(M+1,0));
    puzzle = temp;
    /*全局变量初始化陷阱:不能设置vector<vector<int>> puzzle(N+1,vector<int>(M+1,0));
    后再从main函数里面去cin >> N >> M来设置，因为puzzle大小已经在预编译时确定 */
    for(int i = 0;i < T;i++){
        cin >> tp_x >> tp_y;
        puzzle[tp_x][tp_y] = 1;
    }
    dfs(sx,sy);

    cout << ans;

    return 0;
}
