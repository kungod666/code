#include <iostream>
using namespace std;
struct note
{
    int x;
    int y;
    int s;
};
int main()
{
    note que[2501];
    int tail,head;
    head = 1;
    tail = 1;
    int startx,starty,n,m,p,q;
    int a[50][50];
    int book[50][50];
    cout << "欢迎来到由東雪莲赞助播出的缺德导航步数最小系统！\n";
    cout << "请输入您要创造的矩阵大小(行,列均不大于49)\n";
    cin >> n >> m;
    cout << "请输入矩阵参数(0表示可通过,1表示有障碍)\n";
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            cin >> a[i][j];
        }
    }
    cout << "请输入起始点x,y\n";
    cin >> startx >> starty;
    cout << "请输入终点p,q\n";
    cin >> p >> q;
    que[tail].x = startx;
    que[tail].y = starty;
    que[tail].s = 0;
    tail++;
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    //右下左上顺序
    while(head < tail)
    {
        int flag = 0;
        int tpx;
        int tpy;
        for(int k = 0;k < 4;k++)
        {
            tpx = que[head].x +next[k][0];
            tpy = que[head].y +next[k][1];
            if(tpx < 1 || tpx > n ||tpy < 1||tpy > m) continue;
            if(a[tpx][tpy] != 1 && book[tpx][tpy] != 1)
            {
                book[tpx][tpy] = 1;
                que[tail].x = tpx;
                que[tail].y = tpy;
                que[tail].s = que[head].s + 1;
                tail++;
            }
            if(tpx == p && tpy == q)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1) break;
        head++;
    }
    cout << "到达目的地最小步数是：" << que[tail-1].s << "\n";
}