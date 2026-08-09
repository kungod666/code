#include <stdio.h>
#include <stdlib.h>
//Dijkstra不能处理负权
typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 0x10000

typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Grph;

typedef struct{
    int begin;
    int end;
    int weight;
}Edge;


void create_graph(Mat_Grph* G){
    G->vertex_num = 9;
    G->edge_num = 16;
    for(int i = 0;i <9;i++){
        G->vertex[i] = i;
    }
    for(int i = 0;i <G->vertex_num;i++){
        for(int j = 0;j < G->vertex_num;j++){
            if(i == j){
                G->arc[i][j] = 0;
            }
            else{
                G->arc[i][j] = MAX;
            }
        }
    }
    /*先记录弧尾部*/
    G->arc[0][1] = 1;
    G->arc[0][2] = 5;

    G->arc[1][2] = 3;
    G->arc[1][3] = 7;
    G->arc[1][4] = 5;

    G->arc[2][4] = 1;
    G->arc[2][5] = 7;

    G->arc[3][4] = 2;
    G->arc[3][6] = 3;

    G->arc[4][5] = 3;
    G->arc[4][6] = 6;
    G->arc[4][7] = 9;

    G->arc[5][7] = 5;

    G->arc[6][7] = 2;
    G->arc[6][8] = 7;

    G->arc[7][8] = 4;

    for(int i = 0;i < G->vertex_num;i++){
        for(int j = 0;j <G->vertex_num;j++){
            G->arc[j][i] = G->arc[i][j];
            //j,i顺序保证正确无向
        }
    }
}

//返回下一次要观察哪个顶点
int choose(int distance[],int found[],int vertex_num){
    int min = MAX;
    int minPos = -1;
    for(int i = 0;i < vertex_num;i++){
        if(distance[i] < min && found[i] == 0){
            min = distance[i];
            minPos = i;
        }
    }
    return minPos;
}

void dijkstra(Mat_Grph G,int begin){
    int found[MAXSIZE]; //顶点是否已走过
    int path[MAXSIZE];//每个顶点的最短路径上的前驱顶点（即路径中到达该顶点之前的那个顶点）
    int distance[MAXSIZE]; //begin到每一个顶点之间的最短距离
    for(int i = 0;i < G.vertex_num;i++){
        found[i] = 0;
        path[i] = -1;
        distance[i] = G.arc[begin][i];
    }//初始化

    found[begin] = 1;
    distance[begin] = 0;

    int next;//下一个要观察的点
    for(int i = 1;i < G.vertex_num;i++){
        next = choose(distance,found,G.vertex_num);
        found[next] = 1;
        for(int j = 0;j < G.vertex_num;j++){
            if(found[j] == 0){
                if(distance[next]+G.arc[next][j] < distance[j]){
                    distance[j] = distance[next]+G.arc[next][j];
                    path[j] = next;
                }
            }
        }
    }
}