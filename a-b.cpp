#include <iostream>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <utility>
#include <string>
//第一次用对数器debug而非ai，开心喵
/* −1×10^{100000}≤A,B≤10^{100000}*/
using namespace std;
bool dengshipanduan(string a,string b);
pair<string,string> decideBig(string a,string b)
{
    pair<string,string> tp;
    long m = a.size();
    long n = b.size();
    if(m > n)
    {
        tp.first = a;
        tp.second = b;
    }
    else if(m < n)
    {
        tp.first = b;
        tp.second = a;
    }
    else if(m == n)
    {
        if(dengshipanduan(a,b)||a==b)
        {
            tp.first = a;
            tp.second = b;
        }
        else {//else情况：a<b
            tp.first = b;
            tp.second = a;
        }
    }
    return tp;
}
string add(string a,string b)//传进来的应是正整数,若-a-b单独考虑加-
//a-(-b)，则传入字符串应为b.substr(1);若为-a-b，则传进a.substr(1)
{
    pair<string,string> rece = decideBig(a,b);
    string da = rece.first;
    long da_size = da.size();
    string xiao = rece.second;
    long xiao_size = xiao.size();
    reverse(da.begin(),da.end());
    reverse(xiao.begin(),xiao.end());
    int carry = 0;
    int sum=0;
    int val=0;
    for(int i = 0;i < xiao_size || carry != 0;i++)
    {
        if(i >=xiao_size&&i <da_size)
        {
            sum = (da[i]-'0') +carry;
            val = sum%10;
            carry = sum /10;
            da[i] = val+'0';
        }
        else if(i >=da_size)
        {
            da +="1";
            carry = 0;
        }
        else if(i < xiao_size)
        {
            sum = (da[i]-'0')+(xiao[i]-'0')+carry;
            val = sum % 10;
            carry = sum /10;
            da[i] = val + '0';
        }
    }
    reverse(da.begin(),da.end());
    return da;
}
bool dengshipanduan(string a,string b)//减法的符号判断函数，以此判断是否加负号(a-b)
{
    return a>b;
}
string _minus(string a,string b)//默认是a-b，若是-a-(-b)则将第一个参数换为b,a传进a.substr(1)
{
    pair<string,string> rece = decideBig(a,b);
    string da = rece.first;
    long da_size = da.size();
    string xiao = rece.second;
    long xiao_size = xiao.size();
    reverse(da.begin(),da.end());
    reverse(xiao.begin(),xiao.end());
    int borrow = 0;
    for(int i = 0;i < da_size;i++)
    {
        int cur_digit = da[i]-'0'-borrow;
        borrow = 0;
        int sub_digit = (i<xiao_size)?(xiao[i]-'0') : 0;
        if(cur_digit < sub_digit)
        {
            cur_digit +=10;
            da[i] = cur_digit-sub_digit+'0';
            borrow = 1;
            continue;
        }
        da[i] = cur_digit-sub_digit+'0';
    }
    int pos = da_size;
    for(int j = da_size-1;j>=1;j--)
    {
        if(da[j]!='0') break;
        pos--;
    }
    string tp = da.substr(0,pos);
    reverse(tp.begin(),tp.end());
    return tp;
}
string a_b(string a,string b)
{
    int choice;
    if(a[0]!='-'&&b[0]=='-')
    {
        choice = 1;
    }
    else if(a[0]!='-'&&b[0]!='-')
    {
        choice = 2;
    }
    else if(a[0]=='-'&&b[0]!='-')
    {
        choice = 3;
    }
    else if(a[0]=='-'&&b[0]=='-')
    {
        choice = 4;
    }
    pair<string,string> m;
    switch(choice)
    {
        case 1:
        return add(a,b.substr(1));
        break;

        case 2:
        m = decideBig(a,b);
        if(m.first == b&&a != b) return  "-"+_minus(a,b);
        else return _minus(a,b);
        break;

        case 3:
        return "-"+add(a.substr(1),b);
        break;

        case 4:
        m = decideBig(b.substr(1),a.substr(1));
        if(m.first == a.substr(1)&&a.substr(1)!=b.substr(1)) return "-"+_minus(b.substr(1),a.substr(1));
        else return _minus(b.substr(1),a.substr(1));
    }
}
bool comperator()
{
    int testTime = 100;//测试次数
    int q;
    string result1;
    string result2;
    for(int i = 1;i <=testTime;i++)
    {
        if(i %2 == 0)
        {
            q = -1;
        }
        else q = 1;
        int n = ((rand()%10000)+1)*q;
        int m = ((rand()%10000)+1)*q;
        result1 = to_string(n-m);
        result2 = a_b(to_string(n),to_string(m));
        if(result1 != result2)
        {
            cout << "存在错误" << "\n";
            cout << "initial digit" << n << " " << m << "\n";
            cout <<"normal:" << result1 << " " <<"a-b:"<< result2 << "\n";
        }
    }
    return true;
}
int main()
{
    string a,b;
    cin >> a >> b;
    cout << a_b(a,b);
    return 0;
}