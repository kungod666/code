#include <stdio.h>
#include <stdlib.h>
//思路：层序遍历确定层数
#define MAXSIZE 100
typedef int ElemType;

typedef struct TreeNode{
    ElemType weight;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef TreeNode* BiTree;

int idx = 0;
int weight[] = {100,42,15,-1,-1,27,-1,-1,
58,28,13};

void createTree(BiTree* T){
    if(weight[idx] == -1){
        *T = NULL;
        return;
    }
    *T =(BiTree)malloc(sizeof(TreeNode));
    ElemType num = weight[idx++];
    (*T)->weight = num;
    createTree((&(*T)->left));
    createTree((&(*T)->right));
}

ElemType wplSolve(BiTree root){
    if(root == NULL) return 0;
    //空树wpl为0
    int wpl = 0;
    BiTree queue[MAXSIZE];
    int front = 0;
    int rear = 0;

    int depth = 0;//depth此处为0是便于满足wpl用边数来计算
    queue[rear++] = root;

    while(rear != front){
        int count = rear - front;
        while(count > 0){
            BiTree curr = queue[front++];
            count--;
            if(curr->left == NULL && curr->right == NULL){
                wpl += (curr->weight)*depth;
                //叶子结点方计入wpl计算
                continue;
            }
            if(curr->left != NULL){
                queue[rear++] = curr->left;
            }
            if(curr->right != NULL){
                queue[rear++] = curr->right;
            }
        }
        depth++;
    }
    return wpl;
}