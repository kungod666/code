#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
/*累加和大于等于target的最短子数组长度:
给定一个含有n个正整数的数组和一个正整数target
找到累加和>=target 的长度最小的子数组并返回长度
如果不存在符合条件子数组返回0*/
int panbie(const vector<int>& A,int tar)
{
    int min_num = INT_MAX;
    int sum = 0;
    int left = 0;
    for(int right = 0;right < A.size();right++)
    {
        sum += A[right];
        while(sum >= tar)
        {
            min_num = min(right-left+1,min_num);
            sum -= A[left++];
        }
    }
    return min_num == INT_MAX ? 0 : min_num;
}
int main()
{
    int n,tar;
    cin >> n >> tar;
    vector<int> A(n);
    for(int i = 0;i < A.size();i++)
    {
        cin >> A[i];
    }
    cout << panbie(A,tar) << "\n";
}