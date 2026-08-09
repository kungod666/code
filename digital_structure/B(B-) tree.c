/*问题背景：现实中，很多查找操作不在内存中完成，而是访问磁盘和数据库
。相比内存，磁盘读写代价非常高，必须减少磁盘访问次数。此时，二叉排序树
就显得力不从心，因为高度容易过大---->多路平衡查找树（平衡多叉树）
（B 树）*/

/*一个m阶B树满足以下性质(3阶B树<-->二三树(两个结点或三个结点))
1.每个节点最多m个孩子
2.每隔非根非叶节点至少有[m/2]个孩子
3.每个节点有k个关键字，则要么没有孩子，要么孩子数为k+1
（当一个结点有孩子时，k最大为m-1）
4.关键字按照中序遍历是有序的
5.所有叶子节点在同一层*/
/*注意：关键字在节点中是排好序的，孩子在关键字之间穿插，每个孩子对于一个区间*/

//二三树代码实现
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode{
    int n;                 // 关键字个数（1 或 2）
    int keys[2];           // 键数组(最多两个，对应 3 阶 B 树 / 二三树)
    struct TreeNode* children[3]; // 孩子指针(最多 3 个)
    bool leaf;             // 是否为叶子节点
}TreeNode;

TreeNode* createNode(bool leaf){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->n = 0;
    node->leaf = leaf;
    for(int i = 0;i < 3;i++){
        node->children[i] = NULL;
    }
    return node;
}

int findKey(TreeNode* node,int key){
    int idx = 0;
    while(idx < node->n && key > node->keys[idx]){
        idx++;
    }
    return idx;//返回第一个大于等于key的下标或n
}
TreeNode* search(TreeNode* root,int key,int* pos){
    if(root == NULL) return NULL;
    int i = findKey(root, key);
    if(i < root->n && key == root->keys[i]){
        *pos = i;
        return root;
    }
    if(root->leaf){
        return NULL;
    }
    return search(root->children[i],key,pos);
    //i由findKey维护保证search递归进入正确子孩子节点
}

// 递归插入，返回是否产生“上溢”需要向父结点提升关键字
// 如果需要上溢：*upKey 为提升的关键字，*newChild 为新右子树
int insertRec(TreeNode* node, int key, int* upKey, TreeNode** newChild){
    // 叶子结点
    if(node->leaf){
        if(node->n == 1){
            // 叶子是 2-结点，插进去变成 3-结点（两个关键字）
            if(key < node->keys[0]){
                node->keys[1] = node->keys[0];
                node->keys[0] = key;
            }else{
                node->keys[1] = key;
            }
            node->n = 2;
            return 0; // 不需要向上分裂
        }else{
            // 叶子是 3-结点（两个关键字），插入会临时产生 3 个关键字，需要分裂
            int temp[3];
            temp[0] = node->keys[0];
            temp[1] = node->keys[1];
            temp[2] = key;
            // 排序 3 个关键字
            for(int i = 0;i < 3;i++){
                for(int j = i+1;j < 3;j++){
                    if(temp[j] < temp[i]){
                        int t = temp[i];
                        temp[i] = temp[j];
                        temp[j] = t;
                    }
                }
            }
            // 中间关键字上移
            *upKey = temp[1];
            // 当前结点变成左子：只保留最小的关键字
            node->keys[0] = temp[0];
            node->n = 1;

            // 新建右子：保留最大的关键字
            TreeNode* right = createNode(true);
            right->keys[0] = temp[2];
            right->n = 1;

            *newChild = right;
            return 1; // 向父结点报告“我被分裂了”
        }
    }

    // 内部结点
    int idx = findKey(node, key);
    TreeNode* child = node->children[idx];

    int childUpKey;
    TreeNode* childNewRight = NULL;
    int needSplit = insertRec(child, key, &childUpKey, &childNewRight);

    if(!needSplit){
        return 0;
    }

    // 子结点分裂，childUpKey 需要插入到当前结点
    if(node->n == 1){
        // 当前是 2-结点，插入后变成 3-结点
        if(idx == 0){
            // 插到 keys[0] 之前
            node->keys[1] = node->keys[0];
            node->keys[0] = childUpKey;
            node->children[2] = node->children[1];
            node->children[1] = childNewRight;
        }else{
            // 插到 keys[0] 之后
            node->keys[1] = childUpKey;
            node->children[2] = childNewRight;
        }
        node->n = 2;
        return 0;
    }else{
        // 当前是 3-结点（两个关键字），再插入一个会产生上溢，需要继续向上分裂
        int tempKeys[3];
        TreeNode* tempChild[4];

        // 合并原有 key 和 childUpKey
        if(idx == 0){
            tempKeys[0] = childUpKey;
            tempKeys[1] = node->keys[0];
            tempKeys[2] = node->keys[1];

            tempChild[0] = node->children[0];
            tempChild[1] = childNewRight;
            tempChild[2] = node->children[1];
            tempChild[3] = node->children[2];
        }else if(idx == 1){
            tempKeys[0] = node->keys[0];
            tempKeys[1] = childUpKey;
            tempKeys[2] = node->keys[1];

            tempChild[0] = node->children[0];
            tempChild[1] = node->children[1];
            tempChild[2] = childNewRight;
            tempChild[3] = node->children[2];
        }else{ // idx == 2
            tempKeys[0] = node->keys[0];
            tempKeys[1] = node->keys[1];
            tempKeys[2] = childUpKey;

            tempChild[0] = node->children[0];
            tempChild[1] = node->children[1];
            tempChild[2] = node->children[2];
            tempChild[3] = childNewRight;
        }

        // 中间关键字上移给父亲
        *upKey = tempKeys[1];

        // 当前结点作为左结点，保留最小关键字和左两个孩子
        node->keys[0] = tempKeys[0];
        node->n = 1;
        node->children[0] = tempChild[0];
        node->children[1] = tempChild[1];
        node->children[2] = NULL;

        // 新建右结点，保留最大关键字和右两个孩子
        TreeNode* right = createNode(false);
        right->keys[0] = tempKeys[2];
        right->n = 1;
        right->children[0] = tempChild[2];
        right->children[1] = tempChild[3];
        right->children[2] = NULL;

        *newChild = right;
        return 1;
    }
}

// 插入接口（3 阶 B 树 / 二三树）
void insert(TreeNode** root,int key){
    if(*root == NULL){
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->n = 1;
        return;
    }

    int upKey;
    TreeNode* newChild = NULL;
    int needSplit = insertRec(*root, key, &upKey, &newChild);

    // 根结点分裂，生成新根
    if(needSplit){
        TreeNode* newRoot = createNode(false);
        newRoot->keys[0] = upKey;
        newRoot->n = 1;
        newRoot->children[0] = *root;
        newRoot->children[1] = newChild;
        *root = newRoot;
    }
}

//中序遍历（从小到大输出关键字）
void inorderTraversal(TreeNode* root){
    if(root == NULL) return;

    if(root->leaf){
        //叶子：依次输出关键字
        for(int i = 0;i < root->n;i++){
            printf("%d ", root->keys[i]);
        }
    }else{
        //内部结点：children[0] key[0] children[1] key[1] children[2]
        for(int i = 0;i < root->n;i++){
            inorderTraversal(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        inorderTraversal(root->children[root->n]);
    }
}

//释放整棵树
void freeTree(TreeNode* root){
    if(root == NULL) return;
    if(!root->leaf){
        for(int i = 0;i <= root->n;i++){
            freeTree(root->children[i]);
        }
    }
    free(root);
}

int main(){
    TreeNode* root = NULL;

    int arr[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0;i < n;i++){
        insert(&root, arr[i]);
    }

    printf("中序遍历结果（有序）：");
    inorderTraversal(root);
    printf("\n");

    //简单查找测试
    int key = 12;
    int pos = -1;
    TreeNode* res = search(root, key, &pos);
    if(res != NULL){
        printf("找到关键字 %d ，所在结点位置下标：%d\n", key, pos);
    }else{
        printf("未找到关键字 %d\n", key);
    }

    freeTree(root);
    return 0;
}