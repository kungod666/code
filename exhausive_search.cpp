#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_set>
/*编写一个程序，读取由 n 个元素组成的序列 A 和一个整数 M，
如果可以通过在 A 中的元素相加得到 M，则输出“yes”，
否则输出“no”。 一个元素只能使用一次。
给出序列 A 和 q 个问题，其中每个问题都包含Mi*/
using namespace std;
int main()
{
    vector<int> A;
    vector<int> B; //不要用set！set会去除相同元素导致后续cout yes/no漏情况
    vector<int> index;
    unordered_set<int> sum;
    int n,q;
    cin >> n;
    for(int i = 0;i < n;i++)
    {
        int tp;
        cin >> tp;
        A.push_back(tp);
    }
    int max = 1 << n;
    for(int mask = 1;mask < max;mask++)
    {
        int to = 0;
        int j;
        for(j = 0;j < n;j++)
        {
            if(mask & (1 << j) )
            {
                to += A[j];
            }
        }
        sum.insert(to);
    }
    cin >> q;
    for(int i = 0;i < q;i++)
    {
        int tp;
        cin >> tp;
        B.push_back(tp);
    }
    for(auto it : B)
    {
        if(sum.find(it) != sum.end())
        {
            cout << "yes" << "\n";
        }
        else {
        cout << "no" << "\n";
        }
    }
    return 0;
}