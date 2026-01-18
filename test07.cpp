/*有一个长度为 n 的数组 a（下标从1开始）。我们定义，一个区间 [l, r] 的价值是该区间内所有元素的异或和（即 a[l] ^ a[l+1] ^ ... ^ a[r]）。
现在有 q 次询问。每次询问给你一个区间 [L, R]，请你找出 [L, R] 中价值最大的子区间，并输出这个最大的价值。
输入：第一行两个整数 n, q。第二行 n 个整数表示数组 a。接下来 q 行，每行两个整数 L, R 表示一次询问。
输出：对于每个询问，输出一行一个整数，表示答案。
数据范围：1 <= n <= 5000, 1 <= q <= 1e5, 0 <= a[i] < 2^20。*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    vector<int> prefix_xor(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix_xor[i] = prefix_xor[i - 1] ^ a[i];
    }
    
    while (q--) {
        int L, R;
        cin >> L >> R;
        
        int max_xor = 0;
        
        // 对于每个查询，枚举所有可能的子区间 [i, j]，其中 L <= i <= j <= R
        for (int i = L; i <= R; i++) {
            for (int j = i; j <= R; j++) {
                // [i, j] 区间的异或和 = prefix_xor[j] ^ prefix_xor[i-1]
                int current_xor = prefix_xor[j] ^ prefix_xor[i - 1];
                max_xor = max(max_xor, current_xor);
            }
        }
        
        cout << max_xor << "\n";
    }
    
    return 0;
}