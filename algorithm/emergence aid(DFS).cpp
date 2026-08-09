#include <vector>
#include <iostream>
#include <climits>
using namespace std;
vector<vector<int>> allpaths;
void qianwang(int N,vector<vector<int>> & route,int S,int D,vector<int>& cur,vector<bool> & visited) //DFS搜索
{
    visited[S] = true;
    cur.push_back(S);
    if(route[S][D] != -1)
    {
        vector<int> complete = cur;
        complete.push_back(D);
        allpaths.push_back(complete);
    }
    for(int i = 0;i < N;i++)
    {
        if(i != S&&i != D&&!visited[i]&&route[S][i]!=-1)
        {
        qianwang(N,route,i,D,cur,visited);
        }
    }

    //回溯
    visited[S] = false;
    cur.pop_back();
}
int main()
{
    int N,M,S,D;//N城市,M快道,S出发城市,D目的地
    while(cin >> N >> M >> S >> D)
    {
        vector<int> peo_num(N);
        for(int i = 0;i < N;i++)
        {
            cin >> peo_num[i];
        }
        vector<vector<int>> route(N,vector<int>(N));
        int a,b,c;
        for(int i = 0;i < M;i++)
        {
            cin >> a >> b >> c;
            route[a][b] = c;
        }
        for(int i = 0;i < N;i++)
        {
            for(int j =0;j < N;j++)
            {
                if(route[i][j] == 0&&i != j) route[i][j] = -1;
            }
        }
        vector<bool> visited(N);
        for(int i = 0;i < N;i++)
        {
            visited[i] = false;
        }
        vector<int> cur;
        qianwang(N,route,S,D,cur,visited);
        int min = INT_MAX;//确定最短路径
        vector<int> chazhao;
        for(auto it : allpaths)
        {
            int tp = 0;
            for(auto m = it.begin();m != --it.end();m++)
            {
                tp += route[*m][*(m+1)];
            }
            chazhao.push_back(tp);
            if(min > tp) min = tp;
        }
        vector<vector<int>> minroute;
        /*for(auto it : allpaths)
        {
            int tp = 0;
            for(auto m = it.begin();m != --it.end();m++)
            {
                tp += route[*m][*(m+1)];
            }
            if(min == tp) minroute.push_back(it);
        }*/
        for(int i = 0;i < N;i++)
        {
            if(*(chazhao.begin()+i) == min) minroute.push_back(allpaths[i]);
        }
        int max = 0;//确定最多兵数
        vector<int> bin;
        for(auto it : minroute)
        {
            int tp = 0;
            for(auto m = it.begin();m != it.end();m++)
            {
                tp+=peo_num[*m];
            }
            bin.push_back(tp);
            if(tp > max) max = tp;
        }
        vector<int> zuizhong;
        for(int i = 0;i < minroute.size();i++)
        {
            if(*(bin.begin()+i) == max) zuizhong = minroute[i];
        }
        cout << minroute.size() << " " << max << "\n";
        for(auto it = zuizhong.begin();it != zuizhong.end();it++)
        {
            cout << *it;
            if(it != zuizhong.end()-1) cout << " ";
        }
        allpaths.clear();
    }
    return 0;
}