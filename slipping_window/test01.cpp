#include <iostream>
using namespace std;
int bill_count(int a,int b)
{
    int count = 0;
    while(b+100*(count) < a)
    {
        count++;
    }
    return count;
}
int main()
{
    int a,b;
    cin >> a >> b;
    cout << bill_count(a,b) << "\n";
}