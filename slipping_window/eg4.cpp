#include <iostream>
#include <vector>
using namespace std;
//加油站的良好出发点
/*N个加油站组成一个环形，给定两个长度都是N的非负数组gas和cost
gas[i]代表第i个加油站存的油量，cost[i]代表从第i个加油站到下一个加油站需要消耗的油量
如果从第i个加油站出发能够最终回到该加油站，则第i个加油站就是良好出发点*/
int chufadian(vector<int> gas,vector<int> cost)
{
    int n = gas.size();
    for(int l = 0,r = 0,sum;l < n/*出发点不能超出范围(如果超出即不限制则无限循环)*/;l=r+1,r = l)//设计很好，取余不用考虑r怎么变化，只要加1即可
    {
        int total = 0;
        while(sum + gas[r%n]-cost[r%n] >= 0)
        {
            if(r-l+1 == n) return l; // 检查是否已经转一圈
            sum += gas[r%n]-cost[r%n];
            r++; //右扩
        }
    }
    return -1;
}
int main()
{
    int n;
    cin >> n;
    vector<int> gas(n);
    vector<int> cost(n);
    for(int i = 0;i < n;i++)
    {
        cin >> gas[i] >> cost[i];
    }
}