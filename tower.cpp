#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> base;
    for(int j = 0;j < n;j++)
    {
        int tp;
        cin >> tp;
        auto it = upper_bound(base.begin(),base.end(),tp);
        if(it == base.end())
        {
            base.push_back(tp);
        }
        else
        {
            *it = tp;
        }
    }
    int size = base.size();
    cout << size << "\n";
}