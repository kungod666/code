/*图是由顶点的有穷非空集合和顶点之间边的集合组成*/
//对于图这种数据结构，不允许没有顶点，但边集可以为空

//简单图和多重图
//限制一:顶点不能有从自身指向自身的点
//限制二:同一条边不能出现两次或两次以上
//不满足以上限制则称为多重图

//完全图
/*对于一个具有n个顶点的无向图，边数最大为n(n-1)/2
  对于一个具有n个顶点的有向完全图，边数最大为n(n-1)*/

//路径和路径长度
/*路径:从一个顶点开始，经过一系列的边到达另外一个顶点的顶点序列
  （简单路径:路径中不出现相同顶点)
  (简单回路:除第一个顶点和最后一个顶点,无重复点)
  路径长度:路径上边的条数*/

//顶点的度
/*度:对于无向图，顶点度是与顶点相关联边的数目
入度:有向图,对于顶点v，箭头指向v的边的数目
出度:有向图，对于顶点v，由顶点v出发的边的数目*/

//度与边的关系
/*在无向图中，假设n个顶点，e条边
则图中所有度数之和等于边数的两倍
对于有向图,所有顶点出度之和与入度之和相等，且弧的数量相等*/

//连通图
/*在无向图中,若v->n有路径，则v到n连通
若任意两个顶点均连通，则称为连通图*/

//连通分量
/*无向图中的极大连通子图称为连通分量
(极大:极大顶点数)*/

//强连通图
/*在有向图中，对于每一对顶点v和w，从v到w和从w到v都有路径
则称该有向图是强连通图

有向图中的极大强连通分量是有向图强连通分量*/

//生成树
/*生成树:指含有图中全部顶点的极小连通子树
注意:包含所有顶点n,但只有足以一棵树的n-1条边*/


//十字链表
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20   // 最大顶点数

// 边的信息（如权值），本例中简化为整型权值，不需要时可定义为 void*
typedef int InfoType;

// 弧结点（边结点）
typedef struct ArcBox {
    int tailvex, headvex;            // 弧尾、弧头在顶点数组中的下标
    struct ArcBox *hlink, *tlink;    // 入边链表指针、出边链表指针
    InfoType info;                    // 边的权值或其他信息
} ArcBox;

// 顶点结点
typedef struct VexNode {
    char data;                        // 顶点数据（假设为字符类型）
    ArcBox *firstin, *firstout;       // 入边链表头、出边链表头
} VexNode;

// 十字链表图结构
typedef struct {
    VexNode xlist[MAX_VERTEX_NUM];    // 顶点数组
    int vexnum, arcnum;               // 当前顶点数和弧数
} OLGraph;

// 查找顶点下标（假设顶点数据为字符）
int LocateVex(OLGraph *G, char v) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->xlist[i].data == v)
            return i;
    }
    return -1;
}

// 创建有向图（十字链表）
void CreateDG(OLGraph *G) {
    printf("请输入顶点数和弧数（用空格分隔）：");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    getchar();  // 吸收换行符

    // 输入顶点数据
    printf("请输入 %d 个顶点（每个顶点为一个字符，连续输入，无需分隔）：", G->vexnum);
    for (int i = 0; i < G->vexnum; i++) {
        scanf("%c", &G->xlist[i].data);
        G->xlist[i].firstin = G->xlist[i].firstout = NULL;  // 初始化指针
    }
    getchar();  // 吸收换行符

    // 输入弧信息
    printf("请输入 %d 条弧，每条弧格式：弧尾 弧头 权值（用空格分隔）\n", G->arcnum);
    for (int k = 0; k < G->arcnum; k++) {
        char tail, head;
        int weight;
        scanf("%c %c %d", &tail, &head, &weight);
        getchar();  // 吸收换行符

        int i = LocateVex(G, tail);
        int j = LocateVex(G, head);
        if (i == -1 || j == -1) {
            printf("顶点不存在，跳过该弧\n");
            k--;  // 重新输入
            continue;
        }

        // 创建弧结点
        ArcBox *p = (ArcBox*)malloc(sizeof(ArcBox));
        p->tailvex = i;
        p->headvex = j;
        p->info = weight;

        // 头插法插入到顶点 i 的出边链表
        p->tlink = G->xlist[i].firstout;
        G->xlist[i].firstout = p;

        // 头插法插入到顶点 j 的入边链表
        p->hlink = G->xlist[j].firstin;
        G->xlist[j].firstin = p;
    }
}