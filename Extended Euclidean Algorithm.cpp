#include <iostream>
using namespace std;
/*贝祖等式：对于任意整数 a 和 b，存在整数 x 和 y，使得：
ax + by = gcd(a, b)*/
/*扩展欧几里得算法基于以下递归关系：
1.基本情况：如果 b = 0，则 gcd(a, 0) = a，此时 x = 1, y = 0
2.递归步骤：如果 b ≠ 0，则：
计算 gcd(b, a mod b) 并得到系数 x₁, y₁
然后：x = y₁, y = x₁ - ⌊a/b⌋ × y₁*/
long gcd(long da, long xiao) {
    while (xiao != 0) {
        long temp = xiao;
        xiao = da % xiao;
        da = temp;
    }
    return da;
}
pair<int,int> eucli_algori(long da,long xiao)
{
    pair<int,int> tp;
    if(xiao == 0)
    {
        tp.first =1;
        tp.second=0;
    }
    else {
    pair<int,int> tp2 = eucli_algori(xiao,da%xiao);
    tp.first = tp2.second;
    tp.second = tp2.first - (da/xiao)*tp2.second;
    }
    if(tp.first*da +tp.second*xiao == gcd(da,xiao))
    {
    return tp;
    }
    pair<int,int> error(0,0);
    return error;
}
int main()
{
    long a, b;
    cin >> a >> b;
    pair<int,int> out = eucli_algori(a,b);
    cout << out.first << " " << out.second << "\n";
    return 0;
}