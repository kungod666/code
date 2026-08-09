/*最小生成树(应用:拉电线且保证用的电线最少)
1.它是树,即n个节点，且n-1边
2.连接了图中所有顶点
3.所有边权重之和最小*/

//普里姆算法

#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAX 0x7fffffff //表达int最大的值

typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Grph;

char alph[] ={'A','B','C','D','E','F','G'
,'H','I'};

void create_graph(Mat_Grph* G){
    G->vertex_num = 9;
    G->edge_num = 15;
    for(int i = 0;i <9;i++){
        G->vertex[i] = alph[i];
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
    //A-B A-F
    G->arc[0][1] = 10;
    G->arc[0][5] = 11;

    //B-C B-G B-I
    G->arc[1][2] = 18;
    G->arc[1][6] = 16;
    G->arc[1][8] = 12;

    //C-D C-I
    G->arc[2][3] = 22;
    G->arc[2][8] = 8;

    //D-E D-G D-H D-I
    G->arc[3][4] = 20;
    G->arc[3][6] = 24;
    G->arc[3][7] = 16;
    G->arc[3][8] = 21;

    //E-F E-H
    G->arc[4][5] = 26;
    G->arc[4][7] = 7;

    //F-G
    G->arc[5][6] = 17;

    //G-H
    G->arc[6][7] = 19;

    for(int i = 0;i < G->vertex_num;i++){
        for(int j = 0;j <G->vertex_num;j++){
            G->arc[j][i] = G->arc[i][j];
            //j,i顺序保证正确无向
        }
    }
}

void prim(Mat_Grph* G){
    int i,j,k;
    int min;
    int weight[MAXSIZE];//候选边
    int vex_index[MAXSIZE];//值表示出发点，下标表示到达点

    //先从顶点A出发
    for (i = 0; i < G->vertex_num; i++) {
        weight[i] = G->arc[0][i];   // 将初始边权值设为从0到各顶点的权
        vex_index[i] = 0;            // 这些边的起点暂时都是0
    }
    weight[0] = 0;                   // 顶点0加入生成树

    for(i = 1;i < G->vertex_num;i++){
        min = MAX;
        j = 0;
        k = -1;//标记图不连通
        //找到最小的，与之连接
        while(j < G->vertex_num){
            if(weight[j] != 0 && weight[j] < min){
                min = weight[j];
                k = j;
                j++;
            }
        }
        if(k == -1){ //图不连通
            printf("Graph is not connected!\n");
            return;
        }
        printf("(%c, %c)\n",G->vertex[vex_index[k]],G->vertex[k]);
        weight[k] = 0;//k对应顶点不能再在weight被选

        //找新连接点的待选路径
        for(int j = 0;j < G->vertex_num;j++){
            if(weight[j] != 0 && G->arc[k][j] < weight[j])//松弛
            {
                weight[j] = G->arc[k][j];
                vex_index[j] = k;
            }
        }
    }
}