#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
/*问题描述:已知有一个数组，现通过交换实现升序
但每次交换的两个元素的值(不会有相同元素的值)会加和后计入成本，试求出
以最优交换方式交换的最小成本*/
int min_cost(vector<int>& A)
{
    int total = 0;
    vector<int> sorted = A;
    sort(sorted.begin(),sorted.end());
    vector<bool> visited(A.size(),false);
    int min_num = sorted[0];
    for(int i = 0;i < A.size();i++)
    {
        if(visited[i]) continue;
        int sum = 0;
        int cycle_len = 0;
        int min_x = INT_MAX;
        int cur = i;
        int pos;
        //还要考虑自循环(不必计入)
        //oh，并非，即使不考虑自循环，公式计算得到0不影响
        while(!visited[cur])
        {
            cycle_len++;
            sum += A[cur];
            visited[cur] = true;
            pos = lower_bound(sorted.begin(),sorted.end(),A[cur]) - sorted.begin();
            min_x = min(min_x,A[cur]);
            cur = pos;
        }
        if(cycle_len > 1)
        {
        int x1 = sum + (cycle_len-2)*min_x;
        int x2 = sum +(cycle_len+1)*min_num +min_x;
        total += min(x1,x2);
        }
    }
    return total;
}
int main()
{
    int n;
    cin >> n;
    vector<int> A(n);
    for(int i = 0;i < n;i++) cin >> A[i];
    cout << min_cost(A) << "\n";
    return 0;
}