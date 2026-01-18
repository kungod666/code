#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
/*替换子串得到平衡字符串*/
/*有一个只含有'Q''W''E''R'四种字符,且长度为n字符串
n一定为4的整数倍，假如在该字符串中，这四个字符恰好出现n/4次
那么它就是一个平衡字符串
给你一个这样的字符串s，请通过替换一个子串的方式
使原字符串变成一个平衡字符串
子串可以替换为由'Q''W''E''R'四种字符组成的任何样子
请返回待替换子串的最小可能长度
如果原字符串自身就是一个平衡字符串，则返回0*/
int balanced_len(const string& s)
{
    string tp = "QWER";
    map<char,int> index;
    int n = s.length();
    n /= 4;
    int min_len = INT_MAX;
    for(auto it : s)
    {
        index[it]++;
    }
    for(auto it : tp)
    {
        if(index[it] - n > 0) index[it] =n-index[it];
        else index[it] = 0;
    }
    int debt = 0;
    for(auto it : index)
    {
        debt += -1*(it.second);
    }
    if(debt == 0) return 0;//及时剪枝
    int left = 0;
    for(int right = 0;right < s.size();right++)
    {
        if(index[s[right]]++ < 0) debt--;
        while(index[s[left]] > 0) index[s[left++]]--;
        if(debt == 0) min_len = min(min_len,right-left+1);
    }
    return min_len;
}
int main()
{
    string s;
    cin >> s;
    cout << balanced_len(s) << "\n";
}