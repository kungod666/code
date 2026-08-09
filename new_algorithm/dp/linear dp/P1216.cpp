#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<int>> triangle;
vector<vector<int>> dp;
int main(){
    int n;
    cin >> n;
    int ans;
    vector<vector<int>> temp(n+1,vector<int>(n+1,-1));
    triangle = temp;
    dp = temp;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= i;j++){
            cin >> triangle[i][j];
        }
    }
    dp[1][1] = triangle[1][1];
    if(n == 1){
        cout << dp[1][1] << "\n";
        return 0;
    }
    dp[2][1] = dp[1][1]+triangle[2][1];
    dp[2][2] = dp[1][1] + triangle[2][2];
    if(n == 2){
        ans = max(dp[2][1],dp[2][2]);
        cout << ans << "\n";
        return 0;
    }
    for(int i = 3;i <= n;i++){
        for(int j = 1;j <= i;j++){
            if(j == 1){
                dp[i][1] = triangle[i][1] + dp[i-1][1];
                continue;
            }
            else if(j == i){
                dp[i][i] = triangle[i][i]+dp[i-1][i-1];
                continue;
            }
            dp[i][j] = max(dp[i-1][j-1],dp[i-1][j])+triangle[i][j];
        }
    }
    ans = dp[n][1];
    for(int i = 2;i <= n;i++){
        if(dp[n][i] > ans) ans = dp[n][i];
    }
    cout << ans << "\n";
}