//关键路径
/*算法意义
适用于AOE网(网:戴权值的图)
(不仅表示活动先后制约关系，
其边上权值能表示做活动的成本)
求出实际生产中关键路径(该路径上活动必须按时完成)*/

/*etv:事件发生的最早时间(取大数(原因:
取大数（取最大值），是因为一个事件必须等所有指向它的活动都完成)
--->找最长路径!*/

/*ltv:事件最晚发生的时间
由一个点的ltv反推前驱的ltv(取小值)(即n点ltv依靠它的后续节点的小值得)(若是终点则该点etv视作ltv计算)*/

/*关键路径求法:将所有etv = ltv 的顶点全部连起来
(不用担心关键点无法成线----严格证明可知至少一条!)*/

#include <stdio.h>
#include <stdlib.h>

typedef int VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAX 0x7fffffff

typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Graph;

typedef struct EdgeNode{
    int edge_vex;
    int weight;
    struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode{
    int in;
    VertexType data;
    EdgeNode* head;
}VertexNode;

typedef VertexNode Adj_List[MAXSIZE];

typedef struct{
    Adj_List adj_list;
    int vertex_num;
    int edge_num;
}Adj_Graph;

typedef Adj_Graph* Adj_List_Graph;

int top = -1;
int stack[MAXSIZE];

void push(int e){
    if(top > MAXSIZE){
        printf("满了\n");
        return;
    }

    top++;
    stack[top] = e;
}

int pop(){
    if(top == -1){
        printf("空的\n");
        return 0;
    }

    int elem = stack[top];
    top--;
    return elem;
}

int is_empty(){
    if(top == -1){
        return 0;
    }
    else{
        return 1;
    }
}

void create_graph(Mat_Graph* G){
    G->vertex_num = 10;
    G->edge_num = 13;

    for(int i = 0;i < G->vertex_num;i++){
        G->vertex[i] = i;
    }

    for(int i = 0;i < G->vertex_num;i++){
        for(int j = 0;j < G->vertex_num;j++){
            if(i == j) G->arc[i][j] = 0;
            else G->arc[i][j] = MAX;
        }
    }

    G->arc[0][1] = 3;
    G->arc[0][2] = 4;
    G->arc[1][3] = 5;
    G->arc[1][4] = 6;
    G->arc[2][3] = 8;
    G->arc[2][5] = 7;
    G->arc[3][4] = 3;
    G->arc[4][6] = 9;
    G->arc[5][7] = 6;
    G->arc[6][9] = 2;
    G->arc[7][8] = 5;
    G->arc[8][9] = 3;
}

void create_adj_graph(Mat_Graph G,Adj_List_Graph* ALG){
    EdgeNode* e;
    *ALG = (Adj_List_Graph)malloc(sizeof(Adj_Graph));
    (*ALG)->vertex_num = G.vertex_num;
    (*ALG)->edge_num = G.edge_num;

    for(int i = 0;i < G.vertex_num;i++){
        (*ALG)->adj_list[i].in = 0;
        (*ALG)->adj_list[i].data = G.vertex[i];
        (*ALG)->adj_list[i].head = NULL;
    }

    for(int i = 0;i < G.vertex_num;i++){
        for(int j = 0;j < G.vertex_num;j++){
            if(G.arc[i][j] == 1){
                e = (EdgeNode*)malloc(sizeof(EdgeNode));
                e->edge_vex = j;
                e->weight = G.arc[i][j];
                e->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = e;
                (*ALG)->adj_list[j].in++;
            }
        }
    }
}

void critical_path(Adj_List_Graph ALG){
    EdgeNode* e;
    int top = -1;
    int top2 = -1;
    int stack[MAXSIZE];
    int stack2[MAXSIZE];
    //两个栈，便于逆序求
    int etv[MAXSIZE];
    int ltv[MAXSIZE];
    int curr;
    int k;
    for(int i = 0;i < ALG->vertex_num;i++){
        if(ALG->adj_list[i].in == 0){
            top++;
            stack[top] = i;
        }
    }

    for(int i = 0;i < ALG->vertex_num;i++){
        etv[i] = 0;
    }

    while(top != -1){
        curr = stack[top];
        top--;
        printf("V%d -> ",ALG->adj_list[curr].data);

        top2++;
        stack2[top2] = curr;

        e = ALG->adj_list[curr].head;
        while(e != NULL){
            k = e->edge_vex;
            ALG->adj_list[k].in--;
            if(ALG->adj_list[k].in == 0){
                stack[top++] = k;
            }

            if(etv[curr] + e->weight >etv[k]){
                etv[k] = etv[curr] +e->weight;
            }
            e = e->next;
        }
    }

    printf("End\n");

    printf("etv: ");
    for(int i = 0;i < ALG->vertex_num;i++){
        printf("%d -> ",etv[i]);
    }
    printf("End\n");

    for(int i = 0;i < ALG->vertex_num;i++){
        ltv[i] = etv[ALG->vertex_num-1];
    }

    while(top2 != -1){
        curr = stack2[top2--];

        e = ALG->adj_list[curr].head;
        while(e != NULL){
            k = e->edge_vex;

            if(ltv[k] - e->weight < ltv[curr]){
                ltv[curr] = ltv[k] - e->weight;
            }
            e = e->next;
        }
    }
    //写print函数
}
