#include <iostream>
#include <string>
#include <ctype.h>
#include <functional>
#include <vector>
using namespace std;
vector<long> getnum(string s)
{
    long size = s.size();
    int target2 = 0;
    vector<long> tp;
    for(int i = 0;i <size;i++)
    {
        if(isdigit(s[i]))
        {
            int target1 = i;
            for(target2 =target1;target2<size;target2++)
            {
                if(!isdigit(s[target2])) break;
            }
            tp.push_back(stol(s.substr(target1,target2-target1)));
            i = target2-1;
        }
    }
    return tp;
}
int main()
{
    string s;
    while(cin >> s)
    {
        vector<long> A = getnum(s);
        vector<char> B;
        int s_size = s.size();
        for(int i = 0;i < s_size;i++)
        {
            if(!isdigit(s[i]))
            {
                B.push_back(s[i]);
            }
        }
        long b = B.size();
        int i = 0;
        while(i < B.size())
        {
            if(B[i] == '*' || B[i] == '/')
            {
                long tp;
                switch(B[i])
                {
                    case '*':
                    tp = A[i]*A[i+1];
                    break;
                    case '/':
                    tp = A[i]/A[i+1];
                }
                A[i] = tp;
                A.erase(A.begin()+i+1);
                B.erase(B.begin()+i);
            }
            else {
            i++;
            }
        }
        long sum = A[0];
        for(int i = 0;i < B.size();i++)
        {
            if(B[i] == '+')
            {
                sum+=A[i+1];
            }
            else if(B[i] == '-')
            {
                sum-=A[i+1];
            }
        }
        cout << sum << "\n";
    }
    return 0;
}