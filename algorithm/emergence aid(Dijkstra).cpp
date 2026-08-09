#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int N,M,S,D;
    while(cin >>N >>M >>S >>D)//N城市，M道路，S出发地,D目的地
    {
    vector<int> aid(N);
    for(int i = 0;i < N;i++)
    {
        cin >> aid[i];
    }
    //无向图需存储2*M个边
    vector<int> u(2*M+1),v(2*M+1),w(2*M+1),first(N,-1),next(2*M+1);
    int inf = 99999999;
    vector<int> dis(N,inf);
    dis[S] = 0;
    vector<int> book(N,0);
    vector<int> prev(N,-1);//prev节点设置玄且妙，贪心策略美美爽
    //此处因为只考虑最短路径数量所以选取一个最短路径即可(input保证唯一解)
    vector<int> pathnum(N);
    vector<int> maxaid(N);
    pathnum[S] = 1;
    maxaid[S] = aid[S];
    for(int i = 1;i <= M;i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        u[i] = a;
        v[i] = b;
        w[i] = c;
        next[i] = first[a];
        first[a] = i;
        u[i+M] = b;
        v[i+M] = a;
        w[i+M] = c;
        next[i+M] = first[b];
        first[b] = i+M;
    }
    for(int i =0;i < N-1;i++)
    {
        int min = inf;
        int op = -1;
        for(int j = 0;j < N;j++)
        {
            if(book[j] != 1 && dis[j] < min)
            {
                op = j;
                min = dis[j];
            }
        }
        if(op == -1) continue;
        if(op == D) break;
        book[op] = 1;
        int k = first[op];
        while(k != -1)
        {
            int neighbor = v[k];
            if(dis[neighbor] > dis[op] + w[k])
            {
                dis[neighbor] = dis[op] + w[k];
                pathnum[neighbor] = pathnum[op];
                maxaid[neighbor] = maxaid[op] + aid[neighbor];
                prev[neighbor] = op;
            }
            else if(dis[neighbor] == dis[op] + w[k])
            {
                pathnum[neighbor] += pathnum[op];
                if(maxaid[neighbor] < maxaid[op]+aid[neighbor])
                {
                    maxaid[neighbor] = maxaid[op]+aid[neighbor];
                    prev[neighbor] = op;
                }
            }
            k = next[k];
        }
    }
    cout << pathnum[D] << " " << maxaid[D] << "\n";
    int cur = prev[D];
    vector<int> route;
    route.push_back(D);
    while(cur != -1)
    {
        route.push_back(cur);
        cur = prev[cur];
    }
    for(auto it = route.rbegin();it != route.rend();it++)
    {
        cout << *it;
        if(it != route.rend()-1) cout << " ";
    }
    cout << "\n";
    }
    return 0;
}