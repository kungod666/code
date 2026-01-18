#include <iostream>
#include <climits>
using namespace std;
int n,m,p,q;
int minnum = INT_MAX;
int a[51][51];
int visited[51][51];
void dfs(int startx,int starty,int step)
{
    if(step > minnum) return; //剪枝
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    if(startx == p && starty == q)
    {
        if(step < minnum) minnum = step;
        return;
    }
    visited[startx][starty] = 1;
    for(int k = 0;k < 4;k++)
    {
        int tpx = next[k][0]+startx;
        int tpy = next[k][1]+starty;
        if(a[tpx][tpy] != 1 && visited[tpx][tpy] != 1 && (tpx>=1 && tpx <=n)&&(tpy >=1&&tpy <=m))
        {
            visited[tpx][tpy] = 1;
            dfs(tpx,tpy,step+1);
            visited[tpx][tpy] = 0;
        }
    }
    visited[startx][starty] = 0;
    return;
}
int main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            cin >> a[i][j];
        }
    }
    cin >> p >> q;
    dfs(1,1,0);
    cout << minnum << "\n";
}