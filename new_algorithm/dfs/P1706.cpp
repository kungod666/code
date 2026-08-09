/*按照字典序输出自然数 1 到 n 所有不重复的排列，即 n 的全排列，
要求所产生的任一数字序列中不允许出现重复的数字。*/
#include <iostream>
#include <vector>
using namespace std;
bool stk[10];
int count = 0;
int p[10];
void dfs(int x,int n){
    if(x == n){
        for(int i = 0;i < n;i++){
            cout << "    ";
            cout << p[i];
            if(i == n-1) cout << "\n";
        }
        return;
    }
    for(int i = 1;i <= n;i++){
        if(!stk[i]){
            stk[i] = true;
            p[x] = i;
            dfs(x+1,n);
            stk[i] = false;
        }
    }
}
int main(){
    int n;
    cin >> n;
    for(int i = 0;i < 10;i++){
        stk[i] = false;
    }
    dfs(0,n);
    return 0;
}