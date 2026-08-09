#include <iostream>
#include <stack>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;
int main()
{
    string s;
    while(getline(cin,s))
    {
        string result;
        vector<ll> index;//记录运算符位置
        stack<ll> digit;//存储数字
        stack<char> zifu;//存储字符
        for(ll i = 0;i < s.size();i++)
        {
            if(s[i] != ' ') result += s[i];
        }
        for(ll it = 0;it < result.size();it++)
        {
            if(result[it] == '+')
            {
                index.push_back(it);
                zifu.push('+');
            }
            else if(result[it] == '-')
            {
                index.push_back(it-1);
                zifu.push('+');
            }
        }
        digit.push(stoll(result));
        for(ll i = 0;i < index.size();i++)
        {
            digit.push(stoll(result.substr(index[i]+1)));
        }
        while(!zifu.empty())
        {
            ll tp1 = digit.top();
            digit.pop();
            ll tp2 = digit.top();
            digit.pop();
            char tp = zifu.top();
            switch(tp)
            {
                case '+':
                digit.push(tp1+tp2);
                break;
                case '-':
                digit.push(tp2-tp1);
            }
            zifu.pop();
        }
        cout << digit.top() << "\n";
    }
    return 0;
}