#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    Node* prev;
    Node* next;
};
//头插法
int insertHead(Node* head,int val){
    Node* h = (Node*)malloc(sizeof(Node));
    h->data = val;
    h->prev = head;
    h->next = head->next;
    if(head->next != NULL){
        head->next->prev = h;
    }
    head->next = h;
    return 1;
}
//尾插法
int insertTail(Node* tail,int val){
    Node* h = (Node*)malloc(sizeof(Node));
    if(tail == NULL){
        h->prev = tail->prev;
        tail->prev->next = h;
        return 1;
    }
    tail->next = h;
    h->prev = tail;
    return 1;
}