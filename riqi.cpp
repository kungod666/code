#include <iostream>
using namespace std;

bool isLeapYear(int x) {
    return (x % 400 == 0) || (x % 4 == 0 && x % 100 != 0);
}

int ping[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int run[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

int main() {
    long long ans = 0;
    for (int year = 2240; year <= 9875; ++year) {
        int y[4] = {year / 1000, (year / 100) % 10, (year / 10) % 10, year % 10};
        for (int month = 1; month <= 12; ++month) {
            int m_digits[2], m_len;
            if (month < 10) {
                m_digits[0] = month;
                m_len = 1;
            } else {
                m_digits[0] = month / 10;
                m_digits[1] = month % 10;
                m_len = 2;
            }
            int max_day = isLeapYear(year) ? run[month - 1] : ping[month - 1];
            for (int day = 1; day <= max_day; ++day) {
                int d_digits[2], d_len;
                if (day < 10) {
                    d_digits[0] = day;
                    d_len = 1;
                } else {
                    d_digits[0] = day / 10;
                    d_digits[1] = day % 10;
                    d_len = 2;
                }
                int cnt[10] = {0};
                for (int i = 0; i < 4; ++i) cnt[y[i]]++;
                for (int i = 0; i < m_len; ++i) cnt[m_digits[i]]++;
                for (int i = 0; i < d_len; ++i) cnt[d_digits[i]]++;
                int first = -1;
                bool ok = true;
                for (int i = 0; i < 10; ++i) {
                    if (cnt[i] > 0) {
                        if (first == -1) first = cnt[i];
                        else if (cnt[i] != first) { ok = false; break; }
                    }
                }
                if (ok) ++ans;
            }
        }
    }
    cout << ans << endl;
    return 0;
}