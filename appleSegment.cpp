#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> A(n);
    long long total = 0;
    
    for(int i = 0; i < n; i++) {
        cin >> A[i];
        total += A[i];
    }
    
    long long best = LLONG_MAX;
    
    // 枚举所有可能的子集
    for(int mask = 0; mask < (1 << n); mask++) {
        long long sum = 0;
        for(int i = 0; i < n; i++) {
            if(mask & (1 << i)) {
                sum += A[i];
            }
        }
        long long diff = abs(total - 2 * sum);
        if(diff < best) {
            best = diff;
        }
    }
    
    cout << best << endl;
    return 0;
}