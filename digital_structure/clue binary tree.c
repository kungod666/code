//线索二叉树
#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;

typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode* lchild;
    struct ThreadNode* rchild;
    int ltag;
    int rtag;
}ThreadNode;
/*ltag为0时，指向该节点左孩子，为1时指向前驱;
rtag同理*/
typedef ThreadNode* ThreadTree;

char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;

ThreadTree prev;
/*前提*/
//1.头结点的lchild指向二叉树的根
//2.头结点的rchild指向遍历的最后一个结点
//3.遍历顺序的第一个结点的lchild指向头结点
//4.遍历顺序的最后一个结点的rchild指向头结点

//创建树
void createTree(ThreadTree* T){
    ElemType ch;
    ch = str[idx++];
    if(ch == '#'){
        *T =NULL;
        return;
    }
    *T = (ThreadTree)malloc(sizeof(ThreadNode));

    (*T)->data = ch;

    createTree(&(*T)->lchild);
    if((*T)->lchild != NULL){
        (*T)->ltag = 0;
    }

    createTree(&(*T)->rchild);
    if((*T)->rchild != NULL){
        (*T)->rtag = 0;
    }
}

//具体线索化(中序)
void threading(ThreadTree T){
    if(T != NULL){
        threading(T->lchild);
        if(T->lchild == NULL){
            T->ltag = 1;
            T->lchild = prev;//prev是上一个访问的结点
        }
        if(prev->rchild == NULL){
            prev->rtag = 1;
            prev->rchild = T;
        }
        prev = T;
        threading(T->rchild);
    }
}

//开始线索化
void inOrderThreading(ThreadTree* head,ThreadTree T){
    //头结点
    *head = (ThreadTree)malloc(sizeof(ThreadNode));
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = (*head);

    if(T == NULL){
        (*head)->lchild = *head;
        return;
    }
    (*head)->lchild = T;//完成前提1
    prev = (*head);

    threading(T);

    //最后一个结点线索化
    prev->rchild = *head;
    //最后一次出栈已使prev为最后一个结点
    prev->rtag = 1;

    //头结点右孩子指向最后一个结点
    (*head)->rchild = prev;
}

//使用线索进行中序遍历
void inOrder(ThreadTree T){
    ThreadTree curr;
    curr = T->lchild;

    while(curr != T){
        while(curr->ltag == 0){
            curr = curr->lchild;
        }

        printf("%c ",curr->data);

        while(curr->rtag == 1 && curr->rchild != T){
            curr = curr->rchild;
            printf("%c ",curr->data);
        }
        curr = curr->rchild;
    }
    printf("\n");
}
/*注:关于前序线索非递归遍历只用调整顺序即可,
而后序线索非递归遍历较困难*/
/*根本原因:前序与中序遍历终点都不是根节点
而是右侧最终结点，这使得p !+= head可以直接
成为判终条件*/