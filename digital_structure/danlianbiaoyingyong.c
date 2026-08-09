#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Node{
    int data;
    Node* next;
}Node;
//删除绝对值相等的节点
void removeNode(Node* L,int n){
    Node* p = L;//L是头节点
    int index;//作为下标
    int* q = (int*)malloc(sizeof(int)*n+1);
    for(int i = 0;i < n+1;i++){
        *(q+i) = 0;
    }
    while(p->next != NULL){
        index = abs(p->next->data);
        if(*(q+index) == 0){
            *(q+index) = 1;
            p = p->next;
            continue;
        }
        else{
            Node* temp = p->next;
            p->next = temp->next;
            free(temp);//free()释放堆内存
        }
    }
    free(q);
}
//反转链表
Node* reverseNode(Node* L){//L传入头节点
    Node* first = NULL;
    Node* second = L->next;
    Node* third;
    while(second != NULL){
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    L->next = first;
    return L;
}
//删除中间节点(处理奇数节点情况，偶数个其实多加个条件判断就可以)
void deleteMid(Node* L){
    Node* slow = L;//slow设置成head目的是获得中间接节点的前置节点(毕竟是单向链表嘛)
    Node* fast = L->next;
    while(fast->next != NULL&&fast != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = temp->next;
    free(temp);
}
//重新排序函数(将a1,a2,a3,...,an-1,an排成a1,an,a2,a3,an-1,...)
void reOrederList(Node* head){
    //确定中间节点
    Node* fast = head->next;
    Node* slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    //反转中间节点右侧链表
    slow->next = NULL;
    Node* first = NULL;
    Node* second = slow->next;
    Node* third = NULL;
    while(second != NULL){
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    //将中间右侧链表向左侧插入
    Node* p1 = head->next;
    Node* p2;
    Node* q1 = first;
    Node* q2;
    while(p1 != NULL && q1 != NULL){
        p2 = p1->next;
        q2 = q2->next;
        p1->next = q1;
        q1->next = p2;
        p1 = p2;
        q1 = q2;
    }//不考虑长度不一致是因为输入数据保证不出现问题
}
//判断链表有环
int isCycle(Node* head){
    Node* fast = head;
    Node* slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        /*实际上fast速度快慢不重要，只要fast速度与slow不等，总有
        某时刻二者相遇，这在离散数学有解*/
        slow = slow->next;
        if(slow == fast){
            return 1;
        }
    }
    return 0;
}
//判断链表中环的起始点
//空间o(1)
Node* locateBegin(Node* head,int flag)//flag状态机
{
    if(flag == 0) return NULL;//由isCycle判断flag状态
    int count = 1;
    Node* slow = head;
    Node* fast = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            fast = fast->next;
            while(fast != slow){
                fast = fast->next;
                count++;
            }
        }
    }
    Node* pre = head;
    Node* cur = head;
    while(count-- > 0){
        cur = cur->next;
    }
    while(pre != cur){
        cur = cur->next;
        pre = pre->next;
    }
    return cur;
}
