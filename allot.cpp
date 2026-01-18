#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*你需要从皮带输送机按顺序(i=0,1,…,n−1)得到 n 包w ikg的包裹.
你应该将所有包裹装载到 k 辆具有共同最大载荷P 的卡车上。
每辆卡车都可以从皮带输送机上装载连续的包裹（大于或等于零），序列中的包裹总重量不得超过最大载荷P。
编写一个程序，读取 n、k和 w i，并报告最大负载 P 的最小值以装载所有包裹。*/
int able(vector<int> A,int p)
{
    int count = 1;
    int sum = 0;
    for(auto it = A.begin();it != A.end();it++)
    {
        if((sum + *it) > p)
        {
            sum = *it;
            count++;
        }
        else
        {
            sum += *it;
        }
    }
    return count;
}
int pmin(vector<int> A,int n,int k)
{
    vector<int> m = A;
    sort(m.begin(),m.end());
    int p = 0;
    int l;
    int r = 0;
    int index;
    if(n <= k)
    {
        p = m[n-1];
        return p;
    }
    else 
    {
        l = m[n-1];
        for(auto it : A)
        {
            r += it;
        }
        while(l <= r)
        {
            index = l+((r-l)>>1);
            if(able(A,index) > k)
            {
                l = index+1;
            }
            else if(able(A,index) <= k)
            {
                r = index-1;
                p = index;
            }
        }
        return p;
    }
}
int main()
{
    int n,k;
    cin >> n >> k;
    vector<int> A(n);
    for(int i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    cout << pmin(A,n,k) << "\n";

    return 0;
}