#include <iostream>
#include<stack>
using namespace std;
/*栈向队列的转换（核心：保证满足先进先出）
实现：创两个栈in与out，当需输出先将in数据倒入out
再把out数据输出
满足原则：1.out空了才能倒
2.如果要倒，则in必须清空*/
bool isEmpty(stack<int> in,stack<int> out)
{
    return in.empty()&&out.empty();
}
void pushin(stack<int>& in)
{
    cout<<"请输入您要输入的数字个数"<< "\n";
    int tp;
    cin >> tp;
    for(int i = 0;i < tp;i++)
    {
        int m;
        cin >> m;
        in.push(m);
    }
}
void pop(stack<int>& in,stack<int>& out)
{
    if(out.empty())
    {
        while(!in.empty())
        {
            out.push(in.top());
            in.pop();
        }
        cout << out.top() << "\n";
        out.pop();
    }
    else {
    cout << out.top() << "\n";
    out.pop();
    }
}
void pb(stack<int>& in)
{
    int tp;
    cout << "请输入你要添加的数字" << "\n";
    cin >> tp;
    in.push(tp);
}
int main()
{
    stack<int> in;
    stack<int> out;
}