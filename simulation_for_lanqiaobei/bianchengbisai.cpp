#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    long x1 = 789456;
    long y1 = 567890;
    long count1 = 1;//901234
    long x2 = 654321;
    long y2 = 876543;
    long count2 = 1;//500001;
    long long ans = 0;
    for(int i = 1;i <= 500001;i++){
        int temp = (i-x1-1)/y1 +1;
        if(temp <= 0) continue;
        ans += count1 >= temp ? temp : count1;
    }
    cout << ans;
}