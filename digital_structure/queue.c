#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct{
    int data[MAXSIZE];
    int rear;//队尾
    int front;//队头
}Queue;
//判断队列是否满
int queueFull(Queue* Q){
    if(Q->front>0)//有出队操作
    {
        int step = Q->front;
        for(int i = Q->front;i <= Q->rear;i++){
            Q->data[i-step] = Q->data[i];
        }
        Q->front = 0;
        Q->rear -= step;
        return 1;
    }
    else{//表明真的满了
        return 0;
    }
}
//入队
int push(Queue* Q,int val){
    if(Q->rear >= MAXSIZE){
        if(!queueFull(Q)) return 0;
    }
    Q->data[Q->rear++] = val;
    return 1;
}