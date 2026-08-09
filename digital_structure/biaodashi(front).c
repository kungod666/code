/*开始解决中缀转后缀的问题*/
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
char expr[] = "(5+3)/2+3*4";//中缀表达式

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
void print_token(int e){
    switch(e){
        case 0:
        printf("(");
        break;
        case 1:
        printf(")");
        break;
        case 2:
        printf("+");
        break;
        case 3:
        printf("-");
        break;
        case 4:
        printf("*");
        break;
        case 5:
        printf("/");
        break;
        case 6:
        printf("%%");
        break;
        default: return;
    }
}
void postfix(stack* s){
    int in_stack[] = {0,19,12,12,13,13,13,0};
    int out_stack[] = {20,19,12,12,13,13,13,0};
    //此为各符号优先级顺序,,数组下标与enum值一一对应
    contentType token;
    int index = 0;
    push(s,EOS);//设立哨兵EOS，避免后续访问越界
    char symbol;
    int e;

    token = getToken(&symbol,&index);

    while(token != EOS){
        if(token == NUM) printf("%c",symbol);
        //此时s为符号栈，遇到数字直接输出
        else if(token == RIGHT_PARE){
            while(s->data[s->top] != LEFT_PARE){
                pop(s,&e);
                print_token(e);
            }
            pop(s,&e);
        }
        else {
            while(in_stack[s->data[s->top]] >= out_stack[token]){
                pop(s,&e);
                print_token(e);
            }
            push(s,token);
        }
        token = getToken(&symbol,&index);
    }
}
//eval()函数缺陷：只能算一位数
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
    postfix(init());
    return 0;
}
