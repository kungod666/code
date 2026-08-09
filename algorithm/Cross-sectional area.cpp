#include <iostream>
#include <stack>
#include <vector>
#include <utility>
using namespace std;
int main()
{
    stack<int> n;
    vector<pair<int,int>> A;
    string q;
    cin >> q;
    int cha;
    int index;
    pair<int,int> tp;
    for(int i = 0;i < q.size();i++)
    {
        if(q[i] == '\\')
        {
            n.push(i);
        }
        else if(q[i] == '_') continue;
        else if(q[i] == '/')
        {
            if(!n.empty())
            {
            index = n.top();
            n.pop();
            cha = i-index;
            tp.first = index;
            tp.second = cha;
            if(!A.empty())
            {
            for(auto it = A.begin();it != A.end();)
            {
              if (tp.first < (*it).first) {
                tp.second = tp.second + (*it).second;
                it = A.erase(it);
              }
              else it++;
            }
            }
            A.push_back(tp);
            }
            else continue;
        }
    }
    int sum = 0;
    for(auto it : A)
    {
        sum += it.second;
    }
    cout << sum << "\n";
    cout << A.size() << " ";
    for(auto it : A)
    {
        cout << it.second << " ";
    }
    return 0;
}