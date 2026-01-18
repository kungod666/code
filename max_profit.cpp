#include <iostream>
#include <set>
using namespace std;
/*您可以从外汇保证金交易中获取利润。 例如，如果您以每美元 100 日元的价格买入 1000 美元，并以每美元 108 日元的价格卖出，则可以获得 (108 - 100) × 1000 = 8000 日元。
你需要编写一个程序，读取一种货币在 t 时刻的价值R t，然后输出Rj−Ri的最大值（j>i）。*/
int main()
{
    set<int> A;
    int n;
    cin >> n;
    int min_val;
    int cur;
    int num1;
    cin >> num1;
    min_val = num1;
    for(int i = 1;i < n;i++)
    {
        cin >> cur;
        A.insert(cur-min_val);
        if(cur < min_val) min_val = cur;
    }
    cout << *(A.rbegin()) << "\n";
    return 0;
}