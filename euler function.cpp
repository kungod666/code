#include <iostream>
#include <math.h>
#include <vector>
#include <set>
using namespace std;
/*欧拉函数：如果已知正整数 n 的质因数分解为：
n = p₁^k₁ × p₂^k₂ × ... × pᵣ^kᵣ
（其中 p₁, p₂, ..., pᵣ 是不同的质数，k₁, k₂, ..., kᵣ 是对应的指数）

那么，欧拉函数的计算公式为：
φ(n) = n × (1 - 1/p₁) × (1 - 1/p₂) × ... × (1 - 1/pᵣ)*/
set<int> zhiyinshu(int n)
{
    set<int> tp;
    if(n == 1)
    {
        tp.insert(1);
        return tp;
    }
    while(n % 2 == 0)
    {
        tp.insert(2);
        n /= 2;
    }
    for(int i = 3;i*i <= n;i+=2)
    {
        while(n % i ==0)
        {
            tp.insert(i);
            n /= i;
        } //从小到大遍历，保证加入的i一定为质数
    }
    if(n > 1) 
    {
        tp.insert(n);
    }
    return tp;
}
int euler_function(int n)
{
    set<int> rece = zhiyinshu(n);
    int count = n;
    for(auto it : rece)
    {
        count *= (1-(1*1.0/it*1.0));
    }
    return count;
}
int main()
{
    int n;
    cin >> n;
    cout << euler_function(n) << "\n";
    return 0;
}