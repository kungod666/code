/*平衡二叉树：又称AVL树，是一种二叉排序树，
任意一个节点的左子树与右子树的绝对值不超过1*/

//平衡因子=左子树的高度-右子树的高度

/*最小不平衡子树：从插入点向上回溯，第一个失衡的点，对失衡的平衡二叉树
进行调整时，需要先找到最小不平衡子树*/

#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode{
    int data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int height;
}TreeNode;
typedef TreeNode* BiTree;

int getHeight(BiTree T){
    if(T == NULL){
        return 0;
    }
    return T->height;
}

void updateHeight(BiTree T){
    int lh = getHeight(T->lchild);
    int rh = getHeight(T->rchild);
    T->height = (lh > rh?lh:rh)+1;
}

int balanceNum(BiTree T){
    return getHeight(T->lchild)-getHeight(T->rchild);
}

//右旋（LL时）
BiTree rightRotate(BiTree y){
    BiTree m = y->lchild;
    BiTree n = m->rchild;
    y->lchild = n;
    m->rchild = y;

    updateHeight(y);
    updateHeight(m);
    return m;
}

//左旋
BiTree leftRotate(BiTree x){
    BiTree m = x->rchild;
    BiTree n = m->lchild;
    x->rchild = n;
    m->lchild = x;

    updateHeight(x);
    updateHeight(m);
    return m;
}

BiTree insert_tree(BiTree T,int val){
    if(T == NULL){
        T = (BiTree)malloc(sizeof(TreeNode));
        T->lchild = NULL;
        T->rchild = NULL;
        T->height = 1;
        T->data = val;
        return T; 
    }

    if(T->data > val){
        T->lchild = insert_tree(T->lchild, val);
    }
    else if(T->data < val){
        T->rchild = insert_tree(T->rchild, val);
    }
    else return T;//发现有重复的

    updateHeight(T);
    int balance = balanceNum(T);

    if(balance > 1 && T->lchild->data > val){
        /*也可以用getHeight(T->lchild->lchild) >= getHeight(T->lchild->rchild)
        来判断LR/LL*/
        rightRotate(T);
    }
    else if(balance < -1 && T->rchild->data < val){
        leftRotate(T);
    }
    else if(balance > 1 && T->lchild->data < val){
        leftRotate(T->lchild);
        rightRotate(T);
    }
    else if(balance < -1 && T->rchild->data >val){
        rightRotate(T->rchild);
        leftRotate(T);
    }
    return T;
}