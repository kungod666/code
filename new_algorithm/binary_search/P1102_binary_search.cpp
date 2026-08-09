#include<iostream>
#include <algorithm>
using namespace std;
long a[200001];
long N,C,ans;
int main()
{
    cin>>N>>C;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+N+1);//O(nlogn)
    for(int i=1;i<=N;i++)
    {
        ans+=((upper_bound(a+1,a+N+1,a[i]+C)-a)-(lower_bound(a+1,a+N+1,a[i]+C)-a));
        //lower_bound返回第一个a[i]+C的位置（索引3），upper_bound返回最后一个a[i]+C之后的位置
        //若不存在则结果为0
    }
    cout<<ans;
    return 0;
}
