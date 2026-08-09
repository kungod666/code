#include <stdio.h>
#include <stdlib.h>
//层序遍历判断树的深度(类似BFS)
#define MAXSIZE 100
typedef char ElemType;
typedef struct TreeNode{
    ElemType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

typedef struct{
    TreeNode* data[MAXSIZE];
    int rear;//队尾
    int front;//队头
}Queue;
Queue* initqueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->rear = 0;
    q->front = 0;
    return q;

}

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
int equeue(Queue* Q,TreeNode* val){
    if(Q->rear >= MAXSIZE){
        if(!queueFull(Q)) return 0;
    }
    Q->data[Q->rear++] = val;
    return 1;
}
//出队
void dequeue(Queue* q,TreeNode** m){
    *m = q->data[q->front++];
}
//队列大小
int queueSize(Queue* q){
    return (q->rear)-(q->front);
}
//层序遍历
int maxDepth(TreeNode* root){
    if(root == NULL) return 0;
    int depth = 0;
    Queue* q = initqueue();
    equeue(q,root);
    while(q->front != q->rear)//判断非空
    {
        int count = queueSize(q);
        while(count > 0){
            TreeNode* curr;
            dequeue(q,&curr);
            if(curr->lchild != NULL){
                equeue(q,curr->lchild);
            }
            if(curr->rchild != NULL){
                equeue(q,curr->rchild);
            }
            count--;
        }
        depth++;
    }
    return depth;
}