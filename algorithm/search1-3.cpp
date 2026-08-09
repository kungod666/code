#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n,k;
    cin >> n >> k;
    vector<int> A(n);
    vector<int> B;//存放中位数
    for(int i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    for(int i = 0;i+k-1<n;i++)
    {
        vector<int> tp = A;
        sort(tp.begin()+i,tp.begin()+i+k);//sort是左闭右开的
        if( k % 2 != 0) B.push_back(*(tp.begin()+i+(k-1)/2));
        else if(k % 2 == 0) //B.push_back((*(tp.begin()+(k/2))+*(tp.begin()+i+k-1))/2);
        {
            int miner = min(*(tp.begin()+(k/2)),*(tp.begin()+i+k-1));
            B.push_back(miner);
        }
    }
    for(int it : B)
    {
        cout << it << " ";
    }
    return 0;
}