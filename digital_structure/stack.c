#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
//线性表stack实现
typedef struct{
    int data[MAXSIZE];
    int top;//栈顶指针，但实际上不是指针(下标)
}Stack;
//初始化
void initStack(Stack* s){
    s->top = -1;
}
int isEmpty(Stack* s){
    if(s->top == -1){
        return 1;
    }
    else return 0;
}
//压栈
int push(Stack* s,int val){
    //先判断是否满
    if(s->top >= MAXSIZE-1) return 0;
    s->data[++s->top] = val;
    return 1;
}
//出栈
int pop(Stack* s,int* e){
    if(s->top < 0){
        return 0;
    }
    *e = s->data[s->top--];//*e用以告以外界删除的值具体是多少
    return 1;
}
//获取栈顶元素
int getTop(Stack* s,int* e){
    if(s->top < 0) return -1;
    *e = s->data[s->top];
    return 1;
    //不直接返回元素在于-1不具有特殊性
    //以*e值是否改变更能准确获取top元素
}
//栈动态内存分配
typedef struct{
    int* data;
    int top;
}Stack2;
Stack2* intiStack2(){
    Stack2* s = (Stack2*)malloc(sizeof(Stack2));
    s->data = (int*)malloc(sizeof(int)*MAXSIZE);
    s->top = -1;
    return s;
}
//栈的链式结构实现
typedef struct stack3{
    int data;
    struct stack3* next;
}Stack3;
Stack3* intiStack3(){
    Stack3* s = (Stack3*)malloc(sizeof(Stack3));
    s->next = NULL;
}
void push3(Stack3* s,int val){
    Stack3* h = (Stack3*)malloc(sizeof(Stack3));
    h->data = val;
    if(s->next == NULL){
        s->next = h;
        h->next = NULL;
    }
    h->next = s->next;
    s->next = h;
}
int pop3(Stack3* s,int* e){
    Stack3* temp = s->next;
    if(temp != NULL){
    s->next = temp->next;
    *e = temp->data;
    free(temp);
    return 1;
    }
    return 0;
}
int getTop3(Stack3* s,int* e){
    if(s->next == NULL){
        return 0;
    }
    *e = s->next->data;
    return 1;
}