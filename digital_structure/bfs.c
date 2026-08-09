#include <stdio.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100


typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Grph;

int visited[MAXSIZE];
int front  = 0;
int rear = 0;
int queue[MAXSIZE];
//队列中数据为int是因为存放的是顶点数组

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
            G->arc[i][j] = 0;
        }
    }
    /*先记录弧尾部*/
    //A-B A-F
    G->arc[0][1] = 1;
    G->arc[0][5] = 1;

    //B-C B-G B-I
    G->arc[1][2] = 1;
    G->arc[1][6] = 1;
    G->arc[1][8] = 1;

    //C-D C-I
    G->arc[2][3] = 1;
    G->arc[2][8] = 1;

    //D-E D-G D-H D-I
    G->arc[3][4] = 1;
    G->arc[3][6] = 1;
    G->arc[3][7] = 1;
    G->arc[3][8] = 1;

    //E-F E-H
    G->arc[4][5] = 1;
    G->arc[4][7] = 1;

    //F-G
    G->arc[5][6] = 1;

    //G-H
    G->arc[6][7] = 1;

    for(int i = 0;i < G->vertex_num;i++){
        for(int j = 0;j <G->vertex_num;j++){
            G->arc[j][i] = G->arc[i][j];
            //j,i顺序保证正确无向
        }
    }
}

void bfs(Mat_Grph G){
    int i = 0;
    visited[i] = 1;
    printf("%c\n",G.vertex[i]);
    queue[rear++] = i;
    while(front != rear){
        i = queue[front++];
        //不同于层序遍历中while以count作为条件
        //只需保证不为空即可遍历完成(不用依靠count计算depth)
        for(int j = 0;j < G.vertex_num;j++){
            if(G.arc[i][j] == 1 && visited[j] == 0){
                visited[j] = 1;
                printf("%c\n",G.vertex[j]);
                queue[rear++] = j;
            }
        }
    }
}

int main(){
    Mat_Grph G;
    create_graph(&G);

    for(int i = 0;i <G.vertex_num;i++){
        visited[i] = 0;
    }
    bfs(G);

    return 0;
}