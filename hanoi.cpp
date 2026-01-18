#include <iostream>
using namespace std;
void hanoi(int n,char F,char A,char T)
{
    if(n == 1){
        cout << "move " << n << " from " << F << " to "
        << T << "\n";
        return;
    }
    hanoi(n-1,F,T,A);
    cout << "move " << n << " from " << F << " to "
        << T << "\n";
    hanoi(n-1,A,F,T);
}
int main()
{
    int n;
    char F,A,T;
    cin >> n;
    F = 'F';
    A = 'A';
    T = 'T';
    hanoi(n,F,A,T);
    return 0;
}