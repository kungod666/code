#include <iostream>
#include <vector>
using namespace std;
//单向图
int main()
{
    int n,m;//n为图顶点,m为道路条数
    cout << "请输入城市数以及道路条数\n";
    cin >> n >> m;
    vector<int> u(m+1),v(m+1),w(m+1),first(n+1),next(m+1);
    //初始化first数组
    for(int i = 1;i <=n;i++)
    {
        first[i] = -1;
    }
    for(int i = 1;i <=m;i++)
    {
        cout << "请输入道路所经城市及距离\n";
        cin >> u[i] >> v[i] >> w[i];
        next[i] = first[u[i]];
        first[u[i]] = i; //fisrt[u[i]]保存u[i]城市的第一条道路编号
    }
    cout << "请输入起始点\n";
    int x;
    cin >> x;
    int inf = 99999999;
    vector<int> dis(n+1,inf);
    dis[x] = 0;
    //录入dis信息
    /*for(int i = 1;i <=n;i++)
    {
        k = first[x];
        if(i == x)
        {
            dis[i] = 0;
            continue;
        }
        while(k != -1)
        {
            if(v[k] == i)
            {
                dis[i] = w[k];
                continue;
            }
            k = next[k];
        }
    }*/
   //上面这段代码不需要，dijsktra算法会处理这个录入
    //求最短路径
    vector<int> book(n+1);//book数组用以记录已访问的顶点
    int min;
    for(int i = 1;i <= n-1;i++)//确定n-1个最小值
    {
        min = inf;
        int op = -1;//记录最小点
        for(int j = 1;j <=n;j++)
        {
            if(dis[j] < min&&book[j] != 1)
            {
                min = dis[j];
                op = j;
            }
        }
        if(op == -1) break;
        book[op] = 1;//已经访问
        int k = first[op];
        while (k != -1) {
            int neighbor = v[k]; // 邻接顶点
            if (book[neighbor] == 0 && dis[op] != inf && 
                dis[op] + w[k] < dis[neighbor]) {
                dis[neighbor] = dis[op] + w[k];
            }
            k = next[k];
        }
    }
    for(int i = 1;i <=n;i++)
    {
        if(dis[i] == 0) continue;
        if(dis[i] == inf) cout << "无法到达" << i << "城市\n";
        cout << "到达" << i << "城市最短路径长度为" << dis[i] << "\n";
    }
}