#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef char ElemType;
//树的性质
//性质1:度之和加1为结点和
//性质2:对于度为m的树，第i层最多m^(i-1)个结点
//性质3:对于度为m的树，总结点数最多(m^h-1)/(m-1)
//性质4：对于有n个结点的完全二叉树，深度为[log(2)n]+1
//二叉树
//性质：若度为2的结点数为n2，叶子结点为n0，则n0=n2+1

//二叉树的存储结构-链式结构
typedef struct TreeNode{
    ElemType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;
typedef TreeNode* BiTree;

typedef struct{
    BiTree arr[MAXSIZE];
    int top;
}Stack;
Stack* init(){
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}
int isEmpty(Stack* s){
    if(s->top < 0) return 1;
    return 0;
}
void push(Stack* s,BiTree T){
    s->arr[++s->top] = T;
}
void pop(Stack* s,BiTree* T){
    if(isEmpty(s)) return;
    *T = s->arr[s->top--];
}

char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

void createTree(BiTree* T){
    /*因为为了改变指针的朝向，所以
    用指针传递(二级指针)*/
    ElemType ch;
    ch = str[idx++];
    if(ch == '#'||ch == '\0'){
        *T = NULL;
        return;
    }
    *T = (BiTree)malloc(sizeof(TreeNode));
    (*T)->data = ch;
    createTree(&((*T)->lchild));
    createTree(&((*T)->rchild));
}


/*递归遍历*/
//前序遍历输出内容
void preOrder(BiTree T){
    if(T == NULL) return;
    printf("%c ",T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);
}

//中序遍历(左->中->右)
void inOrder(BiTree T){
    if(T == NULL) return;
    inOrder(T->lchild);
    printf("%c ",T->data); 
    inOrder(T->rchild);
}
//后序遍历
void postOrder(BiTree T){
    if(T == NULL) return;
    postOrder(T->lchild);
    postOrder(T->rchild);
    printf("%c ",T->data);
}

/*非递归遍历*/
//非递归前序遍历
void iterPreOrder(Stack* s,BiTree T){
    while(T != NULL || !isEmpty(s)){
        while(T != NULL){
            printf("%c ",T->data);
            push(s,T);
            T = T->lchild;
        }
        pop(s,&T);
        T = T->rchild;
    }
}
int main(){
    BiTree T;
    createTree(&T);
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    postOrder(T);
    printf("\n");
    iterPreOrder(init(),T);
    return 0;
}
