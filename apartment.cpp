#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main()
{
    int n,m,k;
    cin >> n >> m >> k;
    //n人数，m公寓数,k期望差值
    vector<int> peo(n);
    vector<int> apa(m);
    vector<bool> book(n,0);
    for(int i = 0;i < n;i++)
    {
        cin >> peo[i];
    }
    for(int i = 0;i < m;i++)
    {
        cin >> apa[i];
    }
    sort(peo.begin(),peo.end());
    sort(apa.begin(),apa.end());
    int count = 0;
    int i = 0,j = 0;
    while(i <n&&j < m)
    {
        if(abs(peo[i]-apa[j])<=k)
        {
            count++;
            i++;
            j++;
            continue;
        }
        else if(apa[j] < peo[i]-k) j++;
        else if(apa[j] > peo[i]+k) i++;
    }
    cout << count << "\n";
}