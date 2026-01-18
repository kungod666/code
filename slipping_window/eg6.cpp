#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
//k个不同整数的子数组
/*给定一个正整数数组nums和一个整数k,
返回nums中好子数组的数目*/
/*如果nums的某个子数组中不同整数的个数恰好为k
则称nums的这个连续，不一定不同的子数组为好子数组*/
int atMostk(const vector<int>& A, int k)
{
    if (k == 0) return 0;
    if (A.empty()) return 0;  
    
    unordered_map<int, int> cnts;
    int distinctCount = 0;    
    int result = 0;
    int left = 0;
    
    for (size_t i = 0; i < A.size(); i++)
    {
        if (cnts[A[i]]++ == 0) distinctCount++;
        
        while (distinctCount > k)
        {
            cnts[A[left]]--;
            if (cnts[A[left]] == 0) distinctCount--;
            left++;
        }
        
        result += static_cast<int>(i - left + 1);
    }
    
    return result;
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
    cout << atMostk(A,k) - atMostk(A,k-1) << "\n";
    //恰好为k
}