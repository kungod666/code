/*小 D 正在玩一款叫做“合成大西瓜”的游戏。在游戏初始时，他拥有无限个“基础西瓜”。
每一个基础西瓜的等级（大小）可以是 0 到 y 之间的任意整数。
小 D 可以把一排相邻的西瓜放进“合成器”中进行合成。
合成后，这一排西瓜会被压缩成一个全新的西瓜。
这个新西瓜的等级，等于刚才那一排西瓜中不同等级的种类数。
例如，假设现在有一排西瓜，等级分别是 [5,4,0,3,3]。
小 D 选中了 [0,3,3] 这一段放进合成器
因为这里面只有 0 和 3 这 2 种不同的等级，所以它们会合成出一个等级为 2 的新西瓜。此时，原来的一排西瓜就变成了 [5,4,2]。
小 D 的终极目标是合成出一个等级刚好为 x 的大西瓜
假设小 D 绝顶聪明，希望能采用最省材料的合成策略。请问，给定目标西瓜的等级 x 和基础西瓜的最高等级 y，他最少需要消耗多少个“初始基础西瓜”才能达成目标？
因为这个数字可能是一个天文数字，你只需要输出最终结果对 998244353 取模（即求余数）后的值即可。*/
#include <iostream>
#include <math.h>
using namespace std;
//998244353
#define MOD 998244353
long long fast_pow(long long initial,long long base,long long exp){
    long long res = initial;
    while(exp){
        if(exp & 1) res =(res * base) % MOD;
        base =base*base % MOD;
        exp >>=1;
    }
    return res;
}
int main(){
    int T;
    cin >> T;
    int count = 0;
    while(count++ < T){
        int x,y;
        cin >> x >> y;
        //y > 0:ans = (y+1)*2^(x-y-1)
        //y == 0:特殊考虑
        long long ans = 0;
        if(y > 0){
            if(x <=y) ans = 1;
            else{
                ans = fast_pow((y+1LL),2,x-y-1);
            }//(y+1LL) 是将inty转变为LL处理
        }
        else if(y == 0){
            if(x == 0) ans = 1;
            else if(x == 1) ans = 2;
            else {
                ans = fast_pow(3LL,2,x-2);
            }
        }
        //for(int i = 0;i < x-y-1;i++){
        //    ans *= 2;
        //    ans %= 998244353;
        //}
        //指数级运算循环处理比较耗时，不如用二分思想即快速幂
        //pow(base,mi)更不适合，因为是double精度
        cout << ans << "\n";
    }
    return 0;
}