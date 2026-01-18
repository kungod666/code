#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;
/*无重复字符的最长子串(书橱长度)*/
int str_len(const string& s)
{
    unordered_map<char,int> A;
    int left = 0;
    int len = 0;
    for(int i = 0;i < s.size();i++)
    {
        A[s[i]]++;
        while(A[s[i]]>1)
        {
            A[s[left++]]--;
        }
        len = max(i-left+1,len);
    }
    return len;
}
int main()
{
    string s;
    cin >> s;
    cout << str_len(s) << "\n";
}