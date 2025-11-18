#include <iostream>
#include <vector>
using namespace std;
bool notEmpty(int L,int R)
{
    if(L >= R) return false;
    return true;
}
int main()
{
    //当总数确定时，直接使用数组实现队列非常方便；
    vector<int> A(0);
    int L,R;
    L = 0;
    R = 0;
    int m;
    cout << "放入1，弹出2" << "\n";
    while(cin >> m)
    {
        switch(m)
        {
            case 1:
            int tp;
            cin >> tp;
            A.push_back(tp);
            R++;
            break;
            case 2:
            if(L == R)
            {
                cout << "队列为空" << "\n";
                A.clear();
                L = 0;
                R = 0;
                break;
            }
            L++;
        }
    }
    int k;
    cout << "访问队首1，访问队尾2" << "\n";
    while(cin >> k)
    {
        switch(k)
        {
            case 1:
            if(notEmpty(L,R))
            {
                cout << A[L] << "\n";
            }
            else cout << "队列已空" << "\n";
            break;
            case 2:
            if(notEmpty(L,R))
            {
                cout << A[R-1] << "\n";
            }
            else cout << "队列已空" << "\n";
        }
    }
    return 0;
}