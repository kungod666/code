//E:读取指令
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
int T;
ll n,c,w;
//oi十年一场空，不开ll见祖宗
//这里n不开long long，n*(n+1)就溢出(int----2e9)
int solve_one(){
    ll len;
    for(len = 1;len <= n;len++){
        ll idx = w-(len*(len-1))/2;
        if(idx%len == 0 && idx >= 0){
            ll a = idx/len;
            if(a >= 1 && a +(len-1) <= n){
            return 1;
            }
        }
    }
    return 0;
}
int main(){
    cin >> T;
    while(T--){
        cin >> n >> c >> w;
        if(w % c != 0){
            cout << -1 << "\n";
            continue;
        }
        if(w == 0){
            cout << 0 << "\n";
            continue;
        }
        w /= c;
        if(w > n*(n+1)/2){
            cout << -1 << "\n";
            continue;
        }
        //vector<ll> sum(n+1);
        //sum[1] = 1;
        //for(int i = 2;i <= n;i++){
        //    sum[i] = sum[i-1] + i;
        //}
        //o(n^2)
        //for(int i = 1;i <= n;i++){
        //   for(int j = i;j <= n;j++){
        //        if(check[(sum[j]-sum[i]+i)] == true) continue;
        //        check[sum[j]-sum[i]+i] = true;
        //    }
        //}
        if(solve_one()) cout << 1 << "\n";
        else cout << 2 << "\n";
        }
}