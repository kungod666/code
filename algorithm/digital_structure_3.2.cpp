#include <iostream>
#include <list>
#include <utility>
using namespace std;
void jincheng(list<pair<string,int>> A,int q)
{
    int time = 0;
    while(!A.empty())
    {
        if((A.front()).second > q)
        {
            A.front().second -=q;
            A.push_back(A.front());
            A.pop_front();
            time += q;
        }
        else if((A.front()).second<=q)
        {
            time += (A.front()).second;
            cout << (A.front()).first << " " << time << "\n";
            A.pop_front();
        }
    }
}
int main()
{
    int n,q;
    cin >> n >> q;
    list<pair<string,int>> A;
    pair<string,int> tp;
    for(int i = 0;i < n;i++)
    {
        cin >> tp.first >> tp.second;
        A.push_back(tp);
    }
    jincheng(A,q);

    return 0;
}