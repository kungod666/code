#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*至少最长子串:对于字符串s(全是英语小写)，要求求出其最长子串，
其中该子串各字符重复次数至少为k次*/
int longestSubstring(string s,int k)
{
    int n = s.length();
    vector<int> cnts(256,0);
    int ans = 0;
    for(int require = 1;require <= 26;require++)
    {
        for(int i = 0;i < 256;i++)
        {
            cnts[i] = 0;
        }
        for(int l = 0,r = 0,collect = 0,satisfy = 0;r < n;r++)
        {
            if(cnts[s[r]]++ == 0) collect++;
            if(cnts[s[r]] == k) satisfy++;
            while(collect > require)
            {
                if(cnts[s[l]] == 1) collect--;
                if(cnts[s[l]] == k) satisfy--;
                cnts[s[l++]]--;
            }
            if(satisfy == require) ans = max(ans,r-l+1);
        }
    }
    return ans;
}
int main()
{
    int k;
    cin >> k;
    string s;
    cin >> s;
    cout << longestSubstring(s,k) << "\n";
}