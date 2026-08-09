#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
ll n,c;
ll ans = 0;
map<ll,ll> check;
vector<ll> nums;
int main(){
    cin >> n >> c;
    vector<ll>tmp(n+1);
    nums = tmp;
    for(int i = 1;i <= n;i++){
        cin >> nums[i];
        check[nums[i]]++;
    }
    for(int i = 1;i <= n;i++){
        if(check.count(nums[i]+c)){
            ans += check[nums[i]+c];
        }
    }
    cout << ans;
}

/*此题还有拓展喵，即另一种用二分的神奇做法*/