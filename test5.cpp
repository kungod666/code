#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
void ccx(int n)
{
    vector<vector<int>> juzhen;
    for(int i = 0;i < n;i++)
    {
        vector<int> tp;
        for(int j = 1;j <= n;j++)
        {
            tp.push_back(j+n*i);
        }
        juzhen.push_back(tp);
    }
    int size = juzhen.size();
    for(int i = 0;i < size;i++)
    {
        if((i+1)%2==0)
        {
            reverse((juzhen[i]).begin(),(juzhen[i]).end());
        }
    }
    for(int i = 0;i < size;i++)
    {
        for(int j = 0;j < n;j++)
        {
            cout << juzhen[j][i] << " ";
        }
        cout << "\n";
    }
}
int main()
{
    int n;
    while(cin >> n)
    {
        ccx(n);
    }
    return 0;
}