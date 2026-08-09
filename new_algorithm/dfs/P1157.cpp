/*排列与组合是常用的数学方法，
其中组合就是从 n 个元素中抽出 r 个元素（不分顺序且 r≤n），
我们可以简单地将 n 个元素理解为自然数 1,2,…,n，从中任取 r 个数。
现要求你输出所有组合。
例如 n=5,r=3，所有组合为：
123,124,125,134,135,145,234,235,245,345。*/
#include <iostream>
#include <iomanip>
using namespace std;
bool stk[22];
int p[22];
void dfs(int x,int r,int n){
    if(x == r){
        for(int i = 0;i < r;i++){
            cout << setw(3) << p[i];
            if(i == r-1) cout << "\n";
        }
        return;
    }
    for(int i = 1;i <= n;i++){
        if(stk[i]) continue;
        if(x > 0){
            if(i < p[x-1]) continue;//组合提前剪枝
        }
        stk[i] = true;
        p[x] = i;
        dfs(x+1,r,n);
        stk[i] = false;
    }
}
int main(){
    int n,r;
    cin >> n >> r;
    for(int i = 0;i < 22;i++){
        stk[i] = false;
    }
    for(int i = 0;i < 22;i++){
        p[i] = -1;
    }
    dfs(0,r,n);

    return 0;
}