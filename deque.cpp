#include <iostream>
#include <deque>
using namespace std;
/*insert x：在链表的开头添加一个键为 x 的元素。
delete x：从链表中删除第一个键为 x 的元素。如果不存在这样的元素，则什么都不做。
deleteFirst：删除列表中的第一个元素。
deleteLast：删除列表中的最后一个元素。
输入*/
//本来应该构建双向链表的，但因为本人懒所以直接用容器
int main()
{
    int n;
    cin >> n;
    int count = 0;
    deque<int> A;
    while(count < n)
    {
        string m;
        int p;
        cin >> m;
        if(m == "insert" || m=="delete")
        {
            cin >> p;
            switch(m[0])
            {
                case 'i':
                A.push_front(p);
                break;
                case 'd':
                for(auto it = A.begin();it !=A.end();it++)
                {
                    if(*it == p) 
                    {
                        A.erase(it);
                        break;
                    }
                }
                
            }
        }
        if(m == "deleteFirst")
        {
            A.pop_front();
        }
        if(m == "deleteLast")
        {
            A.pop_back();
        }
        count++;
    }
    for(auto it : A)
    {
        cout << it << " ";
    }
    return 0;
}