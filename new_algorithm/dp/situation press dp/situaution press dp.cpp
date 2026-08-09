/*状态压缩：一种用二进制位表示集合状态的思想，
通常与dp组合以二进制位表示状态来更新，
用于解决集合划分、子集选取、排列组合等问题
特别是当问题中的某个维度（如元素个数）较小（通常 ≤ 20）时*/




/*糖果店的老板一共有 M 种口味的糖果出售。为了方便描述，我们将 M 种口味编号 1 ∼ M。
小明希望能品尝到所有口味的糖果。遗憾的是老板并不单独出售糖果，而是 K 颗一包整包出售。
幸好糖果包装上注明了其中 K 颗糖果的口味，所以小明可以在买之前就知道每包内的糖果口味。
给定 N 包糖果，请你计算小明最少买几包，就可以品尝到所有口味的糖果。*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int main(){
    int N,M,K;
    cin >> N >> M >> K;
    vector<int> bags(N,0);
    for(int i = 0;i < N;i++){
        int mask = 0;
        for(int j = 0;j < K;j++){
            int flavor;
            cin >> flavor;
            mask |= (1<<(flavor-1));
        }
        bags[i] = mask;//位运算记录状态
    }
    int total = (1 << M);
    int INF = INT_MAX;
    vector<int> dp(total,INF);
    dp[0] = 0;
    for(int i = 0;i < total;i++){
        if(dp[i] == INF) continue;
        for(auto bag : bags){
            int newMask = i|bag;
            if(dp[newMask] > dp[i]+1){
                dp[newMask] = dp[i]+1;
            }
        } 
    }
    if(dp[total-1] == INF) cout << "-1";
    else cout << dp[total-1];
}