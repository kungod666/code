#include<iostream>
#include<cstdio>
#include<queue>
/*算法关键思想:由边界点出发将未在圈内点染色*/
using namespace std;
const int M = 31;            //最大边界是30，我习惯从1，开始存图； 
int map[M][M];                //用于存图； 
bool vis[M][M];                //用于记录是否是边界联通块，或者是‘1’； 
int n,m,a,b,c;                
queue <int > q;                
void bfs(int x, int y)            //蒟蒻今天用的是BFS； 
{
    vis[x][y] = 1 ;            //把初始点标记，初始点一定为边界，不懂得看主函数； 
    q.push(x);                //队列存点； 
    q.push(y);
    while(!q.empty())            //BFS开始 
    {
        int w = q.front();
        q.pop();
        int e = q.front();
        q.pop();
        if(map[w+1][e] == 0 && w != n && !vis[w+1][e] )    vis[w+1][e] = 1,q.push(w+1),q.push(e);        //其实可以用结构体存四个方向，但蒟蒻不想动脑子； 
        if(map[w-1][e] == 0 && w != 1 && !vis[w-1][e] )    vis[w-1][e] = 1,q.push(w-1),q.push(e);
        if(map[w][e+1] == 0 && e != n && !vis[w][e+1] )    vis[w][e+1] = 1,q.push(w),q.push(e+1);
        if(map[w][e-1] == 0 && e != 1 && !vis[w][e-1] )    vis[w][e-1] = 1,q.push(w),q.push(e-1);
    }
}
int main()
{
    cin>>n;
    for(int i = 1 ; i <= n ; i++)
    {
        for(int j = 1 ; j <= n ; j++)
        {
            cin>>map[i][j];                            //输入点，并把为‘1’的点标记； 
            if(map[i][j] == 1)    vis[i][j] = 1;    
        }
    }
                                //下面两个for是枚举边界，我用的方法比较笨，望dalao海涵； 
    for(int i = 1 ; i <= n ; i = i + n - 1 )        
    {                                                //
        for(int j = 1 ; j <= n ; j++)
        {
            if(vis[i][j])    continue;
            bfs(i,j);
        }
    }
    for(int i = 1 ; i <= n ; i = i + n - 1 )        //
    {
        for(int j = 1 ; j <= n ; j++)
        {
            if(vis[j][i])    continue;
            bfs(j,i);            //十分重要！！！把它换过来，枚举另一组边界； 
        }
    }
    for(int i = 1 ; i <= n ; i++)                //
    {
        for(int j = 1 ; j <= n ; j++ )
        {
            if(!vis[i][j])    cout<<"2"<<" ";        //如果未被标记，这一定是闭合‘1’中的‘0’， 输出‘2’； 
            else     cout<<map[i][j]<<" ";;
        }
        cout<<endl;
    } 
    return 0;
}


