#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n,m,c;
ll ground[1005][1005];
ll sum[1005][1005];
int main(){
    cin >> n >> m >> c;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> ground[i][j];
            sum[i][j] = sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+ground[i][j];
        }
    }
    ll ans = -10000000;
    ll x,y;
    for(int i = c;i <= n;i++){
        for(int j = c;j <= m;j++){
            ll tmp = sum[i][j] - sum[i][j-c]-sum[i-c][j]+sum[i-c][j-c];
            if(ans < tmp){
                x = i-c+1;
                y = j-c+1;
                ans = tmp;
            }
        }
    }
    cout << x << " " << y;
}