/*上面的布局可以用序列 2 4 6 1 3 5 来描述，
第 i 个数字表示在第 i 行的相应位置有一个棋子，如下：
行号 1 2 3 4 5 6
列号 2 4 6 1 3 5
这只是棋子放置的一个解。请编一个程序找出所有棋子放置的解。
并把它们以上面的序列方法输出，解按字典顺序排列。
请输出前 3 个解。最后一行是解的总个数*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int n;
vector<int> p;
int ans = 0;
void dfs(int count,int y){
    if(count > n) return;
    if(y <1 || y > n) return;
    for(int i = 0;i < count-1;i++){
        if(abs(count-i-1) == abs(y-p[i])|| y == p[i]) return;
    }
    p[count-1] = y;
    if(count == n){
        ans++;
        if(!(ans>3)){
            for(auto& it: p){
                cout << it << " ";
            }
            cout << "\n";
        }
        return;
    }
    for(int i = 1;i <=n;i++){
        dfs(count+1,i);
    }
}
int main(){
    cin >> n;
    vector<int> temp2(n);
    p = temp2;
    vector<vector<int>> temp(n+1,vector<int>(n+1,0));
    for(int i = 1;i <=n;i++){
        dfs(1,i);
    }
    cout << ans;
}