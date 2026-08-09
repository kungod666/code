
//单调栈
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
int h[1005];
int n,m;
int main(){
    int ans = 0;
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            char tmp;
            cin >> tmp;
            if(tmp == 'F'){
                h[j]++;
            }
            else{
                h[j] = 0;
            }
        }
        stack<int> st;
        h[0] = 0;
        h[m+1] = 0;
        //哨兵下标
        for(int j = 0;j <= m+1;j++){
            while(!st.empty()&&h[st.top()] > h[j]){
                int height = h[st.top()];
                st.pop();
                int width =j - st.top()-1;//必须弹栈后确定width，这样
                //才能找比原来st.top()左边第一个比它小的位置
                ans = max(ans,width*height);
            }
            st.push(j);
        }
    }
    ans *= 3;
    cout << ans;
}