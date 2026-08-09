#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode{
    int n;//关键字数量
    int keys[2];
    struct TreeNode* children[3];
    int leaf;//表明叶子或否
}TreeNode;

typedef TreeNode* BiTree;

BiTree createTree(int leaf,int key){
    BiTree node = (BiTree)malloc(sizeof(TreeNode));
    for(int i = 0;i < 3;i++){
        node->children[i] = NULL;
        if(i < 2){
            node->keys[i] = 0;
        }
    }
    node->leaf = leaf;
    node->keys[0] = key;
    node->n = 1;
    return node;
}

int findKey(BiTree node,int key){
    int idx = 0;
    while(idx < node->n && node->keys[idx] < key){
        idx++;
    }
    return idx; //返回第一个大于等于n或key
}

int insertRec(BiTree node,int key,int* upKey,BiTree* upNode){
    if(node->leaf == 1){
        if(node->n == 1){
            if(key > node->keys[0]){
                node->keys[1] = key;
                node->n = 2;
            }
            else if(key < node->keys[0]){
                node->keys[1] = node->keys[0];
                node->keys[0] = key;
                node->n = 2;
            }
            return 0;//向上级表示不需分裂
        }
        else{
            int temp[3];
            temp[0] = node->keys[0];
            temp[1] = node->keys[1];
            temp[2] = key;
            for(int i = 0;i < 3;i++){
                for(int j = i+1;j < 3;j++){
                    if(temp[i] > temp[j]){
                        int tp = temp[i];
                        temp[i] = temp[j];
                        temp[j] = tp;
                    }
                }
            }
            *upKey = temp[1];//中间关键值上升
            node->n = 1;
            node->keys[0] = temp[0];
            *upNode = createTree(node->leaf, temp[2]);
            return 1;//向上级表示"孩子已分裂"
        }
    }
    //处理内部节点
    int childIndex = findKey(node,key);
    int* upnum= NULL;
    BiTree* upT = NULL;
    int needSplit = insertRec(node->children[childIndex], key, upnum, upT);
    if(!needSplit){
        return 0;
    }
    if(node->n == 1){
        if(childIndex == 0){
            node->keys[1] = node->keys[0];
            node->keys[0] = *upnum;
            node->children[2] = node->children[1];
            node->children[1] = *upT;
        }
        else{
            node->keys[1] = *upnum;
            node->children[2] = *upT;
        }
        node->n = 2;
        return 0;
    }
    else if(node->n == 2){
        int temp1[3];
        BiTree temp2[4];
        if(childIndex == 2){
            temp1[0] = node->keys[0];
            temp1[1] = node->keys[1];
            temp1[2] = *upnum;
            
            temp2[0] = node->children[0];
            temp2[1] = node->children[1];
            temp2[2] = node->children[2];
            temp2[3] = *upT;


            return 1;
        }
        else if(childIndex == 1){
            temp1[0] = node->keys[0];
            temp1[1] = *upnum;
            temp1[2] = node->keys[1];

            temp2[0] = node->children[0];
            temp2[1] = node->children[1];
            temp2[2] = *upT;
            temp2[3] = node->children[2];
        }
        else if(childIndex == 0){
            temp1[0] = *upnum;
            temp1[1] = node->keys[0];
            temp1[2] = node->keys[1];

            temp2[0] = node->children[0];
            temp2[1] = *upT;
            temp2[2] = node->children[1];
            temp2[3] = node->children[2];
        }
        node->n = 1;
        node->children[2] = NULL;
        *upKey = temp1[1];
        *upNode = createTree(node->leaf, temp1[2]);
        (*upNode)->children[0] = temp2[2];
        (*upNode)->children[1] = temp2[3];

        return 1;
    }
}

int insert(BiTree* root,int key){
    if(root == NULL){
        *root = createTree(1, key);
        return 1;
    }
    int* upKey;
    BiTree* upNode;
    int needSplit = insertRec(*root, key, upKey, upNode);
    if(needSplit){
        //根处需分裂-->开新根
        BiTree temp = *root;
        *root = createTree(0, *upKey);
        (*root)->children[0] = temp;
        (*root)->children[1] = *upNode;
        (*root)->n = 1;
        return 1;
    }
    else return 1;
}