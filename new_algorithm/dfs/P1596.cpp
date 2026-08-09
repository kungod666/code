/*由于最近的降雨，水在农夫约翰的田地里积聚了。
田地可以表示为一个 N×M 的矩形（1≤N≤100；1≤M≤100）。
每个方格中要么是水（W），要么是干地（.）。
农夫约翰想要弄清楚他的田地里形成了多少个水塘。
一个水塘是由连通的水方格组成的，
其中一个方格被认为与它的八个邻居相邻。
给定农夫约翰田地的示意图，确定他有多少个水塘。*/
#include <iostream>
#include <vector>
using namespace std;
int N,M;
int ans = 0;
vector<vector<int>> farm;
vector<vector<int>> used;
void dfs(int x,int y){
    if(x < 1 || x > N || y < 1 || y > M) return;
    if(!farm[x][y]) return;
    if(used[x][y]) return;
    used[x][y] = 1;
    dfs(x+1,y);
    dfs(x-1,y);
    dfs(x,y+1);
    dfs(x,y-1);
    dfs(x+1,y+1);
    dfs(x-1,y-1);
    dfs(x-1,y+1);
    dfs(x+1,y-1);
}
int main(){
    cin >> N >> M;
    vector<vector<int>> temp(N+1,vector<int>(M+1,0));
    farm = temp;
    used = temp;
    char temp1;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            cin >> temp1;
            if(temp1 == '.') farm[i][j] = 0;
            else if(temp1 == 'W') farm[i][j] = 1;
        }
    }
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            if(used[i][j] || !farm[i][j]) continue;
            dfs(i,j);
            ans++;
        }
    }
    cout << ans;
}