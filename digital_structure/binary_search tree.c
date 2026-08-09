/*对于二叉排序树,满足以下特性
1.对于树中任意一个节点，其左子树所有节点的值都小于该节点的值
2.对于树中任意一个节点，其右子树上所有节点的值都大于该节点的值
并且左右子树本身也是二叉排序树*/

//---->(log(2)n)+1---->折半查找O(n);二叉排序树O(n)(树的形状很难保证形成类完全二叉树)
//与数的插入顺序有关----->平衡二叉树应运而生 
#include <stdio.h>
#include <stdlib.h>
//定义二叉树节点结构体
typedef int ElemType;
typedef struct TreeNode{
    ElemType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

typedef TreeNode* BiTree;

//用数组模拟先序创建一棵二叉树(-1表示空节点)
int treeArr[] = {70,55,49,30,-1,39,-1,-1,53,-1
,-1,-1,80,75,-1,-1,98,95,-1,-1,-1};
//此时是手动二叉排序树,但后续插入时会自动排序
int idx = 0;

void createTree(BiTree* T){
    ElemType num;
    num = treeArr[idx++];

    if(num == -1){
        *T = NULL;
    }
    else{
        *T = (BiTree)malloc(sizeof(TreeNode));
        (*T)->data = num;
        createTree(&(*T)->lchild);
        createTree(&(*T)->rchild);
    }
}

int search_bst(BiTree T,int value,BiTree parent,BiTree* pos){
    if(T == NULL){
        *pos = parent; 
        return 0;//查找失败(此无用，但插入有用)
    }

    if(T->data == value){
        *pos = T;
        return 1;
    }
    if(T->data < value){
        return search_bst(T->lchild,value,T,pos);
    }
    else{
        return search_bst(T->rchild,value,T,pos);
    }
}

//插入
int insert_bst(BiTree* T,int value){
    BiTree pos;  //parent用于辅助search_bst,pos表示插入位置或已存在位置
    BiTree curr;

    //查找插入位置
    int status = search_bst(*T,value,NULL,&pos);
    if(status == 0){
        //如果未找到,创建新节点
        curr = (BiTree)malloc(sizeof(TreeNode));
        curr->data = value;
        curr->lchild = NULL;
        //如果树为空，新节点为根节点
        if(pos == NULL){
            *T = curr;
        }
        //插入为左子结点
        else if(value<pos->data){
            pos->lchild = curr;
        }
        else if(value > pos->data){
            pos->rchild = curr; 
        }
        return 1;
    }
    else{
        return 0;
    }
}

//删除 
/*叶子结点
直接移除*/
/*一个孩子的节点
让唯一的子节点"顶替"它的位置，保持排序特性不变*/
/*两个孩子的结点
选择1:左子树最大子节点
选择2:右子树最小子节点*/
int Delete(BiTree* d){
    BiTree temp,record;

    if((*d)->lchild == NULL){
        temp = *d;
        *d = (*d)->lchild;
        free(temp);
    }
    else if((*d)->rchild == NULL){
        temp = *d;
        *d = (*d)->rchild;
        free(temp);
    }
    else{
        temp = (*d);
        record = (*d)->rchild;
        while(record->lchild != NULL){
            temp = record;    //修改temp成员的指针朝向，一级即可（不是在对temp修改）
            record = record->lchild;
        }
        (*d)->data = record->data;
        if(temp != *d){
            temp->lchild = record->rchild;
        }
        else{
            temp->rchild = record->lchild;
        }
        free(record);
    }
}
int delete_bst(BiTree* T,int value){
    if(*T== NULL){
        return 0;
    }
    else{
        if((*T)->data == value){
            return Delete(T);
        }
        else if((*T)->data > value){
            return delete_bst(&(*T)->lchild,value);
        }
        else{
            return delete_bst(&(*T)->rchild,value);
        }
    }
}