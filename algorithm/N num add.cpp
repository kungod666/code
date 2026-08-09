#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b)
{
    ll  max = a > b?a:b;
    ll min = a <=b?a:b;
    if(min == 0) return max;
    while(max%min != 0)
    {
        ll tp = max;
        max = min;
        min = tp%min;
    }
    return min;
}
int main()
{
    int N;
    while(cin >> N&&N != 0)
    {
        int count = 0;
        ll intger = 0;
        vector<ll> A;//分子
        vector<ll> B;//分母
        string tp;
        while(count < N)
        {
            cin >> tp;
            int i = 0;
            for(;i < tp.size();i++)
            {
                if(tp[i] == '/') break;
            }
            A.push_back(stoll(tp));
            B.push_back(stoll(tp.substr(i+1)));
            count++;
        }
        ll size = A.size();
        ll k = 0;
        while(k+1 <size)
        {
            ll fenmu = (B[k]/gcd(B[k],B[k+1]))*B[k+1];
            ll fenzi = (fenmu/B[k])*A[k]+(fenmu/B[k+1])*A[k+1];
            ll op = abs(gcd(fenmu,fenzi));
            fenzi /= op;
            fenmu /= op;
            B[k+1] = fenmu;
            A[k+1] = fenzi;
            k++;
        }
        ll ui = abs(gcd(A[size-1],B[size-1]));
        A[size-1] /= ui;
        B[size-1] /= ui;
        intger = A[size-1]/B[size-1];
        A[size-1] = A[size-1]%B[size-1];
        if(intger == 0) 
        {
            if(A[size-1] != 0) cout << A[size-1] << "/" << B[size-1] << "\n";
        }
        else
        {
            if(A[size-1] != 0) cout << intger << " " << A[size-1] << "/" <<  B[size-1] << "\n";
            else cout << intger << "\n";
        }
    }
    return 0;
}