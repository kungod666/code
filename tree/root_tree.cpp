#include <iostream>
#include <vector>
#define MAX 100005
#define NI -1
using namespace std;
struct Node{
    int p,l,r; //左子右兄弟表示法(针对多度树)
};
Node T[MAX];
vector<int> D(MAX,NI);
int root = NI;
void setDepth(int id,int d)
{
    D[id] = d;
    if(T[id].r != NI) setDepth(T[id].r,d);
    if(T[id].l != NI) setDepth(T[id].l,d+1);
}
void printChildren(int u) {
    if (T[u].l == NI) {
        cout << "[]" << endl;
        return;
    }
    cout << "[";
    int cur = T[u].l;
    while (cur != NI) {
        cout << cur;
        cur = T[cur].r;
        if (cur != NI) cout << ", ";
    }
    cout << "]" << endl;
}
void printNode(int u)
{
    if(u == root) cout << "root";
    else if(T[u].l == NI) cout << "leaf";
    else cout << "internal node";
}
void print(int id)
{
    cout << "node ";
    cout << id << ": parent = " << T[id].p << ", "
    << "depth = " << D[id] << ", ";
    printNode(id);
    cout << ", ";
    printChildren(id);
}
int main()
{
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) T[i].p = T[i].l = T[i].r = NI;
    int id,num;
    for(int i = 0;i < n;i++)
    {
        cin >> id >> num;
        if(num == 0) continue;
        vector<int> stored(num);
        for(int j = 0;j < num;j++)
        {
            cin >> stored[j];
            T[stored[j]].p = id;
            if(j == 0) T[id].l = stored[j];
            else T[stored[j-1]].r = stored[j];
        }
    }
    //找到root
    for(int i = 0;i < n;i++)
    {
        if(T[i].p == NI){
            root = i;
            break;
        }
    }
    if(root != NI) setDepth(root,0);
    for(int i = 0;i < n;i++) print(i);
    return 0;
}