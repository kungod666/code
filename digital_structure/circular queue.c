#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct{
    int data[MAXSIZE];
    int rear;
    int front;
}Queue;
/*满队列：(rear+1)%MAXSIZE == front
队尾:(rear+1)%MAXSIZE*/

//入队
int equeue(Queue* Q,int e){
    if((Q->rear + 1)%MAXSIZE == Q->front){
        //(Q->rear + 1)%MAXSIZE是关键公式
        /*其实这个判满依据有Bug,默认牺牲一个存储单元*/
        printf("满了");;
        return 0;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}
//出队
int dequeue(Queue* Q,int* e){
    if(Q->front == Q->rear){
        printf("空了");
        return 0;
    }
    *e = Q->data[Q->front];
    Q->front = (Q->front+1)%MAXSIZE;
    return 1;
}