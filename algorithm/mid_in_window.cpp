#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
vector<int> median_window(const vector<int>& A,int k)
{
    multiset<int> window(A.begin(),A.begin()+k);
    auto mid = next(window.begin(),k%2==0?(k/2)-1:k/2);
    vector<int> medians;
    for(int i = k;;i++)
    {
        medians.push_back(*mid);
        if(i == A.size()) break;
        window.insert(A[i]);
        if(A[i] < *mid) mid--;
        if(A[i-k] <= *mid) mid++;
        window.erase(window.lower_bound(A[i-k]));
    }
    return medians;
}
int main()
{
    int n,k;
    cin >> n >> k;
    vector<int> A(n);
    for(int i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    vector<int> tp = median_window(A,k);
    for(auto it : tp)
    {
        cout << it << " ";
    }
    return 0;
}