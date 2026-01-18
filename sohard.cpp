#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// 提取数字的函数
vector<long> getnum(const string& s) {
    vector<long> tp;
    int size = s.size();
    for (int i = 0; i < size;) {
        if (isdigit(s[i])) {
            int target1 = i;
            while (i < size && isdigit(s[i])) {
                i++;
            }
            tp.push_back(stol(s.substr(target1, i - target1)));
        } else {
            i++;
        }
    }
    return tp;
}

int main() {
    string s;
    while (cin >> s) {
        vector<long> A = getnum(s);  // 获取数字列表
        vector<char> B;  // 存储操作符

        // 提取操作符
        for (int i = 0; i < s.size(); i++) {
            if (!isdigit(s[i])) {
                B.push_back(s[i]);
            }
        }

        // 处理乘法和除法（优先级高）
        vector<long> result;
        result.push_back(A[0]);

        for (int i = 0, j = 0; i < B.size(); i++) {
            if (B[i] == '*' || B[i] == '/') {
                long tp;
                switch (B[i]) {
                    case '*':
                        tp = result[j] * A[i + 1];
                        break;
                    case '/':
                        if (A[i + 1] == 0) {
                            cout << "Error: Division by zero\n";
                            return 1;  // 除零错误，退出程序
                        }
                        tp = result[j] / A[i + 1];
                        break;
                }
                result[j] = tp;  // 更新当前数字
            } else {
                // 对于加法和减法，直接把数字推入
                result.push_back(A[i + 1]);
                j++;  // 更新位置
            }
        }

        // 处理加法和减法
        long sum = result[0];
        for (int i = 1, j = 0; i < result.size(); i++) {
            if (B[j] == '+') {
                sum += result[i];
            } else if (B[j] == '-') {
                sum -= result[i];
            }
            j++;
        }

        cout << sum << "\n";
    }
    return 0;
}
