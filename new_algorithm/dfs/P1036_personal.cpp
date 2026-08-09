#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
long ans = 0;
bool used[21];
long p[21];
long n,k;
int sushu(long num){
    if(num <= 1) return false;
    if(num == 2) return true;
    for(long i = 2;i*i <= num;i++){
        if(num % i == 0) return false;
    }
    return true;
}

void dfs(long x,vector<long>& arr){
    if(x == k){
        long sum = 0;
        for(long i = 0;i < k;i++){
            sum += p[i];
        }
        if(sushu(sum)) ans++;
        return;
    }
    for(long i = 0;i < n;i++){
        if(used[i]) continue; //用used记录下标位置而非值避免丢失重复
        if(x > 0){
            if(arr[i] < p[x-1]) continue;
        }
        p[x] = arr[i];
        used[i] = true;
        dfs(x+1,arr);
        used[i] = false;
    }
}
int main(){
    cin >> n >> k;
    vector<long> arr(n);
    for(long i = 0;i < n;i++){
        cin >> arr[i];
    }
    sort(arr.begin(),arr.end());
    for(long i = 0;i < 21;i++){
        used[i] = false;
    }
    dfs(0,arr);
    cout << ans;
}
/*注：这个代码存在一个比较恼火的逻辑问题，就是比如arr(1,1,2),k = 2
那么(1,1)就会被重复计算导致ans变大，因为约束采用的是非递减约束及下标标记
回溯会导致问题出现*/


/*这个代码中有一点没处理好的是求和需要再次遍历来运算的，
这一点是可以优化的，因为我们完全可以维护一个sum变量从而避免
重复机械的求和操作*/