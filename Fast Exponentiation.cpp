#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#include <bitset>
using namespace std;
long power(long m,long n,long p)
{
    long ans = 1;
    while(n > 0)
    {
        if((n & 1) == 1)
        {
            ans = (ans*m)%p;
        }
        n >>= 1;
        m = (m*m)%p;
    }
    return ans;
}
int main()
{
    long m,n;
    cin >> m >> n;
    long p = pow(10,9)+7;
    cout << power(m,n,p);
    return 0;
}