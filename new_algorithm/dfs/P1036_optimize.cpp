/*P1036（选数求和判素数）：本质也是组合，
但多了求和与素数判断。你遇到的“重复元素”问题，
其实正是组合生成时需要特别注意的地方——如果数组中有重复值，
仅靠值的大小剪枝（如 arr[i] < p[x-1]）是不够的，
因为相同值的不同下标会被视为不同组合，
但题目可能要求去重（取决于具体题意）。*/

//DFS组合模板（start参数）
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n,k;
int ans = 0;
vector<int> A;

bool primer(int num){
    if(num <= 1) return false;
    if(num == 2) return true;
    for(int i = 2;i*i <= num;i++){
        if(num % i == 0) return false;
    }
    return true;
}

void dfs(int x,int start,int sum){
    /*每次递归从 start 开始，保证组合的单调性，天然去重，
    且不需要额外的 used 数组*/
    if(x == k){
        if(primer(sum)) ans++;
        return;
    }
    for(int i = start+1;i < n;i++){
        dfs(x+1,i,sum+A[i]);
    }
}
int main(){
    cin >> n >> k;
    int temp;
    for(int i = 0;i < n;i++){
        cin >> temp;
        A.push_back(temp);
    }
    sort(A.begin(),A.end());
    dfs(0,-1,0);//-1开始，保证第一个for从0->n-1

    cout << ans;
}