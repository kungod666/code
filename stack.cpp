struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
ListNode* reverseList(ListNode* head) {
        if(head == nullptr){
            return nullptr;
        }
        ListNode* f1 = head;
        if(f1->next == nullptr) return head;
        ListNode* f2 = head->next;
        if(f2->next == nullptr){
            f1->next = nullptr;
            f2->next = f1;
            return f2;
        }
        ListNode* f3 = f2->next;
        while(f3 != nullptr){
            if(f1 == head){
                f1->next = nullptr;
                f2->next = f1;
            }
            else{
                f2->next = f1;
            } 
            f1 = f2;
            f2 = f3;
            f3 = f3->next;
        }
        f2->next = f1;
        return f2;
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* newHead = new(ListNode);
        ListNode* temp = nullptr;
        int num = 0;
        ListNode* begin = nullptr;
        ListNode* end = nullptr;
        ListNode* pos = newHead;
        ListNode* cur = head;
        int count = 0;
        while(cur != nullptr){
            count++;
            if(count == left-1) begin = cur;
            else if(count == right + 1) end = cur;

            if(count >= left && count <= right){
                pos->next = new(ListNode);
                pos = pos->next;
                pos->val = cur->val;
                pos->next = nullptr;
                if(num == 0){
                     temp = pos;
                     num++;
                }
            }
            cur = cur->next;
        }
        newHead = reverseList(newHead->next);
        begin->next = newHead;
        temp->next = end;
    }
};