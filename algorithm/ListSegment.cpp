#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode* next;
};
void initi_list(ListNode* m,int n)
{
    int tp;
    for(int i = 0;i < n;i++)
    {
        cin >> tp;
        m->val = tp;
        if(i != n-1)
        {
            m->next = new ListNode;
            m = m -> next;
        }
        m->next = NULL;
    }
}
ListNode* minArea(ListNode* head1,int x)
{
    ListNode* ans = NULL;
    ListNode* k = NULL;
    while(head1 != NULL)
    {
        if(head1->val < x)
        {
            if(ans == NULL)
            {
                ans = new ListNode;
                ans->next = NULL;
                ans->val = head1->val;
                k = ans;
                
            }
            else {
            k->next = new ListNode;
            k = k->next;
            k->val = head1->val;
            k->next = NULL;
            }
        }
        head1 = head1->next;
    }
    return ans;
}
ListNode* elseArea(ListNode* head2,int x)
{
    ListNode* ans = NULL;
    ListNode* p = NULL;
    while(head2 != NULL)
    {
        if(head2->val >= x)
        {
            if(ans == NULL)
            {
                ans = new ListNode;
                ans->next = NULL;
                ans->val = head2->val;
                p = ans;
                
            }
            else {
            p->next = new ListNode;
            p = p->next;
            p->val = head2->val;
            p->next = NULL;
            }
        }
        head2 = head2->next;
    }
    return ans;
}
void printList(ListNode* a)
{
    while(a != NULL)
    {
        cout << a->val << " ";
        a = a->next;
    }
    cout << "\n";
}
int main()
{
    ListNode k1;
    ListNode* m = & k1;
    ListNode* head1 = & k1;
    ListNode* head2 = & k1;
    int n;
    cin >> n;
    initi_list(m,n);
    int x;
    cin >> x;
    printList(minArea(head1,x));
    printList(elseArea(head2,x));
    return 0;
}