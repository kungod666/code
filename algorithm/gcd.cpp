#include <iostream>
using namespace std;

// 辗转相除法求最大公约数
long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long a, b;
    cin >> a >> b;
    cout << gcd(a, b);
    return 0;
}