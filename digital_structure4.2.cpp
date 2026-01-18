#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
int erfen(vector<int> A,set<int> B)
{
    int count = 0;
    sort(A.begin(),A.end());
    int l = 0;
    int r;
    int x;
    int panduan;
    for(auto it : B)
    {
        panduan = 0;
        r = A.size()-1;
        while(l<=r)
        {
            x = l+((r-l)>>1);
            if(A[x] < it)
            {
                l = x+1;
            }
            else if(A[x]>it)
            {
                r = x-1;
            }
            else if(A[x] == it)
            {
                count++;
                panduan = 1;
                break;
            }
        }
        if(panduan)
        {
            l = x;
        }
    }
    return count;
}
int main()
{
    int n,q;
    cin >> n;
    vector<int> A(n);
    for(int i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    cin >> q;
    int tp;
    set<int> B;
    for(int i = 0;i < q;i++)
    {
        cin >> tp;
        B.insert(tp);
    }
    cout << erfen(A,B) << "\n";
    return 0;
}