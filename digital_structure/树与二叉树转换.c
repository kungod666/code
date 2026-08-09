#include <stdio.h>
#include <stdlib.h>
// 一般树节点
typedef struct TreeNode {
    int val;
    struct TreeNode** children;   // 孩子指针数组
    int childCount;
} TreeNode;

// 二叉树节点
typedef struct BinaryTreeNode {
    int val;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

// 创建一般树节点（指定值和子节点数）
TreeNode* createTreeNode(int val, int childCount) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->childCount = childCount;
    node->children = (TreeNode**)malloc(childCount * sizeof(TreeNode*));
    return node;
}
//树转化为二叉树
/*1.加线，在所有兄弟结点之间加一条线
2.去线，对树中的每一个结点，只保留它与第一个孩子结点的
连线，删除它与其它孩子结点之间的连线
3.层次调整，旋转即可*/

// 递归将一般树转换为二叉树（左孩子右兄弟）
BinaryTreeNode* convert(TreeNode* root) {
    if (root == NULL) return NULL;

    // 创建当前节点的二叉树节点
    BinaryTreeNode* bnode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    bnode->val = root->val;
    bnode->left = NULL;
    bnode->right = NULL;

    BinaryTreeNode* prev = NULL;               // 上一个转换后的孩子
    for (int i = 0; i < root->childCount; ++i) {
        BinaryTreeNode* child = convert(root->children[i]); // 递归转换每个孩子
        if (i == 0) {
            bnode->left = child;                // 第一个孩子作为左孩子
        } else {
            prev->right = child;                 // 后续孩子通过右指针连接成兄弟链
        }
        prev = child;
    }
    return bnode;
}

//二叉树转化为树
/*1.加线，若某个结点的左孩子存在，则将这个左孩子的所有
右孩子结点都作为这个结点的孩子。将该结点与这些右孩子结点用线连起来
2.去线，删除二叉树所有结点与其右孩子结点的连线*/

TreeNode* createTreeNode2(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->children = NULL;
    node->childCount = 0;
    return node;
}
// 向一般树节点添加一个孩子（动态扩容）
void addChild(TreeNode* parent, TreeNode* child) {
    parent->childCount++;
    parent->children = (TreeNode**)realloc(parent->children, parent->childCount * sizeof(TreeNode*));
    parent->children[parent->childCount - 1] = child;
}

// 二叉树 -> 一般树转换函数
TreeNode* convertBack(BinaryTreeNode* root) {
    if (root == NULL) return NULL;

    // 创建当前一般树节点
    TreeNode* newNode = createTreeNode2(root->val);

    // 遍历左孩子及其右兄弟链，这些节点都是当前节点的孩子
    BinaryTreeNode* childNode = root->left;
    while (childNode != NULL) {
        // 递归转换每个孩子（childNode本身及其右兄弟链会在递归内部处理）
        TreeNode* childTree = convertBack(childNode);
        addChild(newNode, childTree);
        childNode = childNode->right; // 沿着右指针取下一个兄弟（即下一个孩子）
    }

    return newNode;
}


//多二叉树转化为森林(先二叉树转为树)
/*第一颗二叉树不动，从第二棵树开始，
依次把后一棵二叉树的根节点作为前一
棵二叉树的根节点的右孩子*/

//森林转二叉树
/*从根节点开始，若右孩子存在，则把右孩子结点的连线删除,
而后到prev的右结点重复*/