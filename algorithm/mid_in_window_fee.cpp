#include <iostream>
#include <set>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
vector<double> min_cost(const vector<ll>& nums,ll k)
{
    vector<double> cost;
    multiset<ll> left,right;
    ll l_sum = 0,r_sum = 0;
    for(ll i = 0;i < k;i++)
    {
        left.insert(nums[i]);
        l_sum += nums[i];
    }
    //初始化left,right
    while(left.size() > (k+1)/2)
    {
        ll l_max = *prev(left.end());
        left.erase(prev(left.end()));
        right.insert(l_max);
        r_sum += l_max;
        l_sum -= l_max;
    }
    double median;
    double cost_num = 0;
    for(ll i = k;;i++)
    {
        if(!left.empty() && !right.empty() && *prev(left.end()) > *right.begin())
        {
            ll left_max = *prev(left.end());
            ll right_min = *right.begin();
            
            left.erase(prev(left.end()));
            right.erase(right.begin());
            
            left.insert(right_min);
            right.insert(left_max);
            
            l_sum = l_sum - left_max + right_min;
            r_sum = r_sum - right_min + left_max;
        }
        if(k%2 == 1) median = *prev(left.end());
        else median = ((double)*(prev(left.end()))+(double)*(right.begin()))/2.0;
        cost_num = (left.size()*median - l_sum)+(r_sum - right.size()*median);
        cost.push_back(cost_num);
        if(i == nums.size()) break;
        //删除元素
        if(!left.empty()&&nums[i-k] <= *prev(left.end()))
        {
            l_sum -= nums[i-k];
            if(left.find(nums[i-k])!=left.end())
            {
            left.erase(left.find(nums[i-k]));
            }
        }
        else {
        r_sum -= nums[i-k];
        if(right.find(nums[i-k])!=right.end())
        {
        right.erase(right.find(nums[i-k]));
        }
        }
        //增加元素
        if(left.empty() || nums[i] <= *prev(left.end()))
        {
            left.insert(nums[i]);
            l_sum += nums[i];
        }
        else {
        right.insert(nums[i]);
        r_sum += nums[i];
        }
        //调整(left应该比right多0或1)
        while(left.size() < (k+1)/2)
        {
            ll r_min = *right.begin();
            right.erase(right.begin());
            left.insert(r_min);
            l_sum += r_min;
            r_sum -= r_min;
        }
        while(left.size() > (k+1)/2)
        {
            ll l_max = *prev(left.end());
            left.erase(prev(left.end()));
            right.insert(l_max);
            l_sum -= l_max;
            r_sum += l_max;
        }
    }
    return cost;
}
int main()
{
    // 强制不使用科学计数法
     ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(ios::fixed);
    cout.precision(0);
    //
    ll n,k;
    cin >> n >> k;
    vector<ll> nums(n);
    for(ll i = 0;i < n;i++)
    {
        cin >> nums[i];
    }
    vector<double> tp = min_cost(nums,k);
    for(auto it : tp)
    {
        cout << it << " ";
    }
    return 0;
}