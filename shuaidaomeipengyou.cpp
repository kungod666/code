#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_set>
#include <string>
using namespace std;
int main()
{
    int n;
    while(cin >> n)
    {
    string tp;
    vector<unordered_set<string>> A(n);
    unordered_set<string> total;
    for(int i = 0;i < n;i++)
    {
        int m;
        cin >> m;
        for(int j = 0;j < m;j++)
        {
            cin >> tp;
            A[i].insert(tp);
            total.insert(tp);
        }
    }
    int chaxun;
    cin >> chaxun;
    string kl;
    vector<string> store;
    unordered_set<string> op;
    vector<string> output;
    for(int i = 0;i < chaxun;i++)
    {
        cin >> kl;
        if(op.find(kl) != op.end()) continue;
        store.push_back(kl);
        op.insert(kl);
    }
    for(auto it : store)
    {
        if(total.find(it) != total.end())
        {
            int panbie = 0;
            for(int index = 0;index < n;index++)
            {
                if(A[index].find(it) != A[index].end())
                {
                    if(A[index].size() > 1) 
                    {
                     panbie = 1;
                     break;
                    }
                }
            }
            if(!panbie)
            {
                output.push_back(it);
            }
        }
        else if(total.find(it) == total.end())
        {
            output.push_back(it);
        }
    }
    if(!output.empty())
    {
        for(auto it = output.begin();it != output.end();it++)
        {
           cout << *it;
           if(it != output.end()-1) cout << " ";
        }
        cout << "\n";
    }
    else cout << "No one is handsome\n";
    }
    return 0;
}