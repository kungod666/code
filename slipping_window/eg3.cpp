#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
//最小覆盖子串
/*给你一个字符串s,一个字符串t,
返回s中涵盖所有字符的最小子串
如果s中不存在涵盖t所有字符的子串，
则返回空字符串"""*/
int cover_len(const string& s,const string& t)
{
    if(s.size() < t.size()) return 0;
    vector<int> cnts(256,0);
    int debt = t.size();
    int min_len = INT_MAX;
    for(int i = 0;i < t.size();i++)
    {
        cnts[t[i]]--;
    }
    int left = 0;
    for(int r = 0;r < s.size();r++)
    {
        if(cnts[s[r]]++ < 0) debt--;//不应该只捕捉-1到0
        while(cnts[s[left]] > 0)
        {
            cnts[s[left++]]--;
        }
        if(debt == 0) min_len = min(r-left+1,min_len);
    }
    return min_len == INT_MAX ? 0 : min_len;
}
int main()
{
    string s,t;
    cin >> s >> t;
    if(cover_len(s,t) == 0) cout << "无" << "\n";
    else cout << cover_len(s,t) << "\n";
    return 0;
}