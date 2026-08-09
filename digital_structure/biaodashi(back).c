#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 100
typedef struct{
    int data[MAXSIZE];
    int top;
}stack;
typedef enum{
    LEFT_PARE,RIGHT_PARE,
    ADD,SUB,MUL,DIV,MOD,
    EOS,NUM
}contentType;

stack* init(){
    stack* p = (stack*)malloc(sizeof(stack));
    p->top = -1;
    return p;
}
int isEmpty(stack* p){
    if(p->top <= -1) return 1;
    return 0;
}
void push(stack* p,int e){
    if(p->top == MAXSIZE-1) return;
    p->data[++p->top] = e;
}
void pop(stack* p,int* e){
    if(isEmpty(p)) return;
    *e = p->data[p->top];
    p->top--;
}
int getTop(stack* s,int* e){
    if(isEmpty(s)) return 0;
    *e = s->data[s->top];
    return 1;
}
//解决后缀表达式
char expr[] = "82/2+56*-";

contentType getToken(char* symbol,int* index){
    *symbol = expr[(*index)++];
    switch(*symbol){
        case '(':
        return LEFT_PARE;
        case ')': return RIGHT_PARE;
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '%': return MOD;
        case '\0': return EOS;
        default: return NUM;
    }
}
int eval(stack* s){
    char symbol;
    int op1,op2;
    int index = 0;
    int result;
    contentType token;
    token = getToken(&symbol,&index);
    while(token != EOS){
        if(token == NUM){
            push(s,symbol-'0');
        }
        else{
            pop(s,&op2);
            pop(s,&op1);
            switch(token){
                case ADD:
                push(s,op1+op2);
                break;
                case SUB:
                push(s,op1-op2);
                break;
                case MUL:
                push(s,op1*op2);
                break;
                case DIV:
                push(s,op1/op2);
                break;
                case MOD:
                push(s,op1%op2);
                break;
                default: break;
            }

        }
        token = getToken(&symbol,&index);
    }
    pop(s,&result);
    free(s);
    return result;
}

int main(){
    printf("%d",eval(init()));
    return 0;
}