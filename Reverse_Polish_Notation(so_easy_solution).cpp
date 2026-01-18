#include <iostream>
#include <stack>
#include <ctype.h>
#include <string>
using namespace std;
/*逆波兰表示法是一种表示法，
其中每个运算符都在其所有操作数的后面出现。
例如，表达式(1+2)×(5+4)
可以表示为逆波兰表达式1 2 + 5 4 + ×。
逆波兰表示法的优点之一是它没有括号。*/
/*逆波兰表示法中的表达式是使用栈计算的。
要计算表达式，程序应按顺序读取符号。
如果符号是操作数，则应将相应的值压入栈。
另一方面，如果符号是一个运算符，
程序应该从堆栈中弹出两个元素，执行相应的操作，
然后将结果压入栈。程序应重复此操作。*/
//逆波兰表示法是对"So Easy !!!“的绝佳解法
int main()
{
    string m;
    stack<int> p;
    int a1,a2;
    while(cin >> m)
    {
        if(isdigit(m[0]))
        {
            p.push(stoi(m));
        }
        else 
        {
            a2 = p.top();
            p.pop();
            a1 = p.top();
            p.pop();
            switch(m[0])
            {
                case '+':
                p.push(a1+a2);
                break;
                case '-':
                p.push(a1-a2);
                break;
                case '*':
                p.push(a1*a2);
            }
        }
    }
    cout << p.top() << "\n";

    return 0;
}