#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <math.h>
using namespace std;
bool sushu(int n)
{
    for(int i = 2;i <= sqrt(n);i++)
    {
        if(n % i == 0) return false;
    }
    return true;
}
void insert(int k,set<int>& D,map<int,int>& F)
{
    map<int,int> tp;
    for(int i = 2;i <=k;i++)
    {
        if(k % i ==0 && sushu(i))
        {
            D.insert(i);
            while(k % i == 0)
            {
                k/=i;
                tp[i]++;
            }
        }
    }
    for(auto it : D)
    {
        if(tp[it] > F[it])
        {
            F[it] = tp[it];
        }
    }
}
int main()
{
    map<int,int> A;
    int n;
    cin >> n;
    vector<int> B(n);
    set<int> C;
    for(int i = 0;i < n;i++)
    {
        cin >> B[i];
        insert(B[i],C,A);
    }
    long total = 1;
    for(auto it : C)
    {
        total *= pow(it,A[it]);
    }
    cout << total;
}