#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    struct ListNode* next;
}k1,k2;
ListNode* addList(ListNode* h1,ListNode* h2)
{
    ListNode* ans = new ListNode;
    ListNode* cur = ans;
    int carry = 0;
    for(int sum,val;h1 != NULL || h2 != NULL || carry != 0;h1 = h1 == NULL?NULL:h1->next,h2 = h2 == NULL?NULL:h2->next)
    //这个循环写的真是太美了
    {
        
        sum = ((h1 == NULL) ? 0:h1->val)+ ((h2 == NULL) ? 0:h2->val)+carry;
        val = sum % 10;
        carry = sum /10;
        cur->next = new ListNode;
        cur->next->val = val;
        cur = cur->next;
        cur->next = NULL;
    }
    return ans->next;
}
int main()
{
    k1.next = NULL;
    k2.next = NULL;
    int n,m;
    cin >> n >> m;
    ListNode* tp1 = &k1;
    ListNode* tp2 = &k2;
    ListNode* h1 = &k1; 
    ListNode* h2 = &k2;//h1与h2用于求和两链表相加
    for(int i = 0;i < n;i++)
    {
        int tp;
        cin >> tp;
        tp1->val = tp;
        if(i != n-1)
        {
        tp1->next = new ListNode;
        tp1 = tp1->next;
        }
        tp1->next = NULL;
    }
    for(int i = 0;i < m;i++)
    {
        int tp;
        cin >> tp;
        tp2->val = tp;
        if(i != m-1)
        {
        tp2->next = new ListNode;
        tp2 = tp2->next;
        }
        tp2->next = NULL;
    }
    ListNode* p = addList(h1,h2);
    while(p != NULL)
    {
        cout << p->val;
        p = p->next;
    }
    return 0;
}