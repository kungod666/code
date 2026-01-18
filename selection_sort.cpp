#include <iostream>
#include <vector>
using namespace std;
/*不断地从未排序的部分中
选出最小（或最大）的元素，
将其放到已排序部分的末尾*/
vector<int> selection_sort(vector<int> A,int n)
{
    int count = 0;
    for(int i = 0;i < n-1;i++)
    {
        int mini = i;
        for(int j = i+1;j < n;j++)
        {
            if(A[j] < A[mini])
            {
                mini = j;
                //此举是为了不断将最小元素移至i位置
            }
        }
        if(mini != i)
        {
            swap(A[i],A[mini]);
            count++;
        }
    }
    for(auto it : A)
    {
        cout << it << " ";
    }
    cout << "\n";
    cout << count;
    return A;
}
int main()
{
    int n;
    cin >> n;
    vector<int> A(n);
    for(int i = 0;i < n;i++)
    {
        cin >> A[i];
    }
    selection_sort(A,n);
    return 0;
}