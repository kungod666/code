#include <iostream>
#include <fstream> // 需要添加这个头文件
using namespace std;

int main() {
    // ===== 新增的代码开始 =====
    // 这3行代码会强制程序从 input.txt 读取输入
    // 提交到 Codeforces 时，把这3行注释掉或删除即可
    #ifndef ONLINE_JUDGE // 如果不是在线判题环境（即本地调试）
    freopen("input.txt", "r", stdin); // 重定向标准输入到文件
    #endif
    // ===== 新增的代码结束 =====

    int T;
    cin >> T; // 现在会自动从 input.txt 读取
    for (int i = 0; i < T; i++) {
        int a, b;
        cin >> a >> b; // 自动读取
        int sum = a + b;
        cout << "Case #" << i+1 << " " << sum << endl;
    }
    return 0;
}