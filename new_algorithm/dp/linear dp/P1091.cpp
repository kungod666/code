#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> heights;
int n;
int main(){
    cin >> n;
    vector<int> temp(n);
    heights = temp;
    for(int i = 0;i < n;i++){
        cin >> heights[i];
    }
    vector<int> dp1(n,1);
    vector<int> dp2(n,1);
    priority_queue<int,vector<int>,greater<int>> min_num;
    for(int i = 0;i < n;i++){
        int ans = -1;
        for(int j = 0;j < i;j++){
            if(heights[j] < heights[i]){
                ans = max(ans,dp1[j]);
            }
        }
        dp1[i] = max(ans+1,1);
    }
    for(int i = n-1;i >= 0;i--){
        int ans = -1;
        for(int j = n-1;j > i;j--){
            if(heights[j] < heights[i]){
                ans = max(ans,dp2[j]);
            }
        }
        dp2[i] = max(ans+1,1);
    }
    for(int i = 0;i < n;i++){
        min_num.push(n-dp1[i]-dp2[i]+1);
    }
    cout << min_num.top() << '\n';
}