
//前后缀最值
#include <iostream>
#include <limits.h>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;
ll n;
vector<ll> A;
int main(){
    cin >> n;
    vector<ll> tmp(n+1);
    vector<ll> Sfront(n+1);//前缀和
    vector<ll> Sback(n+1);//后缀和
    A = tmp;
    for(int i = 1;i <= n;i++){
        cin >> A[i];
        if(i == 1) Sfront[i] = A[i];
        else Sfront[i] = Sfront[i-1] + A[i];
    }
    for(int i = n;i >=1;i--){
        if(i == n) Sback[i] = A[i];
        else Sback[i] = Sback[i+1]+A[i];
    }
    ll front_max = Sfront[1];
    ll front_min = Sfront[1];
    ll back_max = Sback[n];
    ll back_min = Sback[n];
    vector<ll> left_max(n+1);
    vector<ll> right_max(n+1);
    for(int i = 2;i <= n;i++){
        ll res1;
        ll res2;
        res1 = abs(front_min)+abs(Sfront[i]-front_min);
        res2 = abs(front_max)+abs(Sfront[i]-front_max);
        left_max[i] = max(res1,res2);
        if(front_max < Sfront[i]){
            front_max = Sfront[i];
        }
        if(front_min > Sfront[i]){
            front_min = Sfront[i];
        }
    }
    for(int i = n-1;i >= 1;i--){
        ll res1;
        ll res2;
        res1 = abs(back_min)+abs(Sback[i]-back_min);
        res2 = abs(back_max)+abs(Sback[i]-back_max);
        right_max[i] = max(res1,res2);
        if(back_max < Sback[i]){
            back_max = Sback[i];
        }
        if(back_min > Sback[i]){
            back_min = Sback[i];
        }
    }
    ll ans = -1;
    for(int i = 1;i <=n-2;i++){
        ans = max(ans,left_max[i]+right_max[i+1]);
        //注意是i+1(左右的终点部分-->1~j,j+1~n)
    }
    cout << ans;
}