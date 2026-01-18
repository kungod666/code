#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 30
#define NIL -1
using namespace std;
struct Node{
    int p,l,r;//因为是二叉树所以不用“左子右兄”
};
Node T[MAX];
vector<int> D(MAX,NIL);
vector<int> H(MAX,NIL);
vector<bool> visited2(MAX,false);
int root;
int getSibling(int u);
void setDepth(int u,int d)
{
    D[u] = d;
    if(T[u].l != NIL)setDepth(T[u].l,d+1);
    if(T[u].r != NIL)setDepth(T[u].r,d+1);
}
int setHeight(int u)
{
    if(visited2[u] == true) return H[u];
    int h1 = 0,h2 = 0;
    if(T[u].l != NIL) h1 = 1 + setHeight(T[u].l);
    if(T[u].r != NIL) h2 = 1 + setHeight(T[u].r);
    H[u] = max(h1,h2);
    visited2[u] = true;
    return H[u];
}
int getSibling(int u)
{
    if(T[u].p == NIL) return NIL;
    if(T[T[u].p].l != NIL && T[T[u].p].l != u) return T[T[u].p].l;
    else if(T[T[u].p].r != NIL && T[T[u].p].r != u) return T[T[u].p].r;
    return NIL;
}
int getDegree(int u)
{
    int count = 0;
    if(T[u].l != NIL) count++;
    if(T[u].r != NIL) count++;
    return count;
}
string Nodetype(int u)
{
    if(u == root) return "root";
    else if(T[u].l == NIL && T[u].r == NIL) return "leaf";
    else return "internal node";
}
void print(int u)
{
    cout << "node " << u << ": "
    << "parent = " << T[u].p << ", "
    << "sibling = " << getSibling(u) << ", degree = " << getDegree(u) << ", depth = "
    << D[u] << ", height = " << H[u] << ", "
    << Nodetype(u) << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) T[i].p = T[i].l = T[i].r = NIL;
    int tp_u,tp_l,tp_r;
    for(int i = 0;i < n;i++)
    {
        cin >> tp_u >> tp_l >> tp_r;
        T[tp_u].l = tp_l;
        T[tp_u].r = tp_r;
        if(T[tp_u].l != NIL) T[tp_l].p = tp_u;
        if(T[tp_u].r != NIL)T[tp_r].p = tp_u;
    }
    for(int i = 0;i < n;i++)
    {
        if(T[i].p == NIL)
        {
            root = i;
            break;
        }
    }
    if(root != NIL)
    {
        setDepth(root,0);
        setHeight(root);
    }
    for(int i = 0;i < n;i++) print(i);
    return 0;
}