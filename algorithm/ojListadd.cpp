#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
struct ListNode{
    int val;
    ListNode* next;
    int biaozhi = 0;
}k1,k2;
int panbie = 1;
int compareNumbers(ListNode* h1, ListNode* h2) {
    int len1 = 0, len2 = 0;
    ListNode* p1 = h1, *p2 = h2;
    
    while(p1) { len1++; p1 = p1->next; }
    while(p2) { len2++; p2 = p2->next; }
    
    if(len1 > len2) return 1;
    if(len1 < len2) return -1;
    

    vector<int> v1, v2;
    p1 = h1; p2 = h2;
    
    while(p1) { 
        v1.push_back(p1->val); 
        p1 = p1->next; 
    }
    while(p2) { 
        v2.push_back(p2->val); 
        p2 = p2->next; 
    }
    
    for(int i = v1.size()-1; i >= 0; i--) {
        if(v1[i] > v2[i]) return 1;
        if(v1[i] < v2[i]) return -1;
    }
    
    return 0; 
}
ListNode* chushihua(ListNode* h,size_t size,string m)
{
    ListNode* ans = h;
    for(int i = size-1;i >=1;i--)
    {
        h->next = new ListNode;
        h = h->next;
        h->val = m[i]-'0';//使用这种方法代替stoi更高效
        h->next = NULL;
        
    }
    if(m[0] == '-')
    {
        ans->next->biaozhi = -1;
    }
    else if(m[0] != '-')
    {
        h->next = new ListNode;
        h = h->next;
        h->val = m[0]-'0';
        h->next = NULL;
    }
    return ans->next;
}
ListNode* listadd(ListNode* h1,ListNode* h2,int count)
{
    if(count == 1) {
        int cmp = compareNumbers(h1, h2);
        if(h1->biaozhi == -1) { 
            if(cmp > 0) {
                panbie = -1;
            } else {
                panbie = 1;
            }
        } else { 
            if(cmp >= 0) {
                panbie = 1;
            } else {
                panbie = -1;
            }
        }
    }
    ListNode* ans = NULL;
    ListNode* cur = NULL;
    ListNode* tp1 = h1;
    ListNode* tp2 = h2;
    int carry = 0;
    for(int sum,val;h1 != NULL || h2 !=NULL || carry != 0;h1 = h1 == NULL?NULL:h1->next,h2 = h2 == NULL?NULL:h2->next)
    {
        if(count == 1)
        {
            if(panbie == 1) {
                int val1 = (h1 == NULL) ? 0 : h1->val;
                int val2 = (h2 == NULL) ? 0 : h2->val;
                
                if(val1 >= val2 + carry) {
                    sum = val1 - val2 - carry;
                    carry = 0;
                } else {
                    sum = val1 + 10 - val2 - carry;
                    carry = 1;
                }
                val = sum;
            } else {
                int val1 = (h1 == NULL) ? 0 : h1->val;
                int val2 = (h2 == NULL) ? 0 : h2->val;
                
                if(val2 >= val1 + carry) {
                    sum = val2 - val1 - carry;
                    carry = 0;
                } else {
                    sum = val2 + 10 - val1 - carry;
                    carry = 1;
                }
                val = sum;
            }
            
            if(ans == NULL) {
                ans = new ListNode;
                ans->val = val;
                ans->next = NULL;
                cur = ans;
            } else {
                cur->next = new ListNode;
                cur = cur->next;
                cur->val = val;
                cur->next = NULL;
            }
            continue;
        }
        else
        {
        sum = ((h1==NULL)?0:h1->val) +((h2==NULL)?0:h2->val);
        val = sum%10;
        if(val >=0)
        {
            if(ans == NULL)
        {
            ans = new ListNode;
            ans->val = val+carry;
            ans->next = NULL;
            cur = ans;
        }
            else 
        {
            cur->next = new ListNode;
            cur = cur->next;
            cur->val = val+carry;
            cur->next = NULL;
        }
        carry = sum/10;
        }
        else
        {
            break;
        }
    }
    }
    return ans;
}
int main()
{
    string a,b;
    cin >> a >> b;
    ListNode* h1 = &k1;
    ListNode* h2 = &k2;
    h1->next = NULL;
    h2->next = NULL;
    size_t size1 = a.size();
    size_t size2 = b.size();
    h1 = chushihua(h1,size1,a);
    h2 = chushihua(h2,size2,b);
    int count = ((h1->biaozhi == -1)?1:0)+((h2->biaozhi == -1)?1:0);
    ListNode* he = listadd(h1,h2,count);
    vector<int> A;
    while(he != NULL)
    {
        A.push_back(he->val);
        he = he->next;
    }
    if(count == 2) cout << "-";
    else if(panbie == -1) cout << "-";
    for(auto it=A.rbegin();it != A.rend();it++)
    {
        if(it == A.rbegin() && *it == 0)
        {
            continue;
        }
        else {
        cout << *it;
        }
    }
    return 0;
}