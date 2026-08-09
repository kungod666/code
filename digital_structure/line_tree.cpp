/*线段树应用场景:
1.需要频繁查询区间和
2.需要修改元素(单点修改)
时复:O(logn)*/
/*值得一提的是，线段树并非仅仅用于区间和，我们可以把tree[node]值
定义为某区间最大值*/
#include <iostream>
using namespace std;
typedef long long ll;
ll arr[100010] = {0},tree[5000050] = {0};
//arr为存储数据的数组，tree是存线段树的数组
void build(int node,int start,int end){
    //建树函数，参数是根节点和左右区间
    if(start == end){
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end)>>1;
    build(2*node,start,mid);
    build(2*node+1,mid+1,end);
    tree[node] = tree[2*node]+tree[2*node+1];
}
void update(int node,int start,int end,int pos,int delta){
    if(start == end){
        tree[node] += delta;
        //找到了要修改的节点
        return;
    }
    int left = 2*node;
    int right = 2*node+1;
    int mid = (start+end)>>1;
    if(pos >= start && pos<= mid){
        update(left,start,mid,pos,delta);
    }
    else update(right,mid+1,end,pos,delta);
    tree[node] = tree[left]+tree[right];
}
int query(int node,int start,int end,int pl,int pr){
    //pl为目标查询区间左端点，pr同理
    if(start >= pl&&end<= pr){
        return tree[node];
    }//边界检查
    int mid = (start+end)>>1;
    int left = 2*node;
    int right = 2*node+1;
    int ans = 0;
    if(pl <= mid){
        ans += query(left,start,mid,pl,pr);
    }
    if(pr >mid){
        ans += query(right,mid+1,end,pl,pr);
    }
    return ans;
}
int main(){
    //3 1 4 7 2 4 42 31 8 9 23 21 18 17 67 14 81 90 41 50
    for(int i = 1;i <= 20;i++){
        cin >> arr[i];
    }
    build(1,1,20);
    int tp;
    while(cin >> tp){
        switch(tp){
            case 1:
            int n,m;
            cin >> n >> m;
            cout << query(1,1,20,n,m) << "\n";
            break;
            case 2:
            int pos,delta;
            cin >> pos >> delta;
            update(1, 1, 20, pos, delta);
            break;
            case 3:
            break;
        }
    }
    return 0;
}