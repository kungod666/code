//差分核心:我不直接存最终结果，我存的是“变化的斜率/差值”
//任何一个格子的标记，都不单独对应“上方”或“左边”，而是对应“右下方整个无限矩形”。
#include <iostream>
//b[i][j]=a[i][j]-a[i-1][j]-a[i][j-1]+a[i-1][j-1]
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define all(x) x.begin(),x.end()
using namespace std;
const double eps=1e-8;
const double PI=acos(-1.0);
typedef long long ll;
template<class T>int chkmin(T &a,T b){return a>b?a=b,1:0;}
template<class T>int chkmax(T &a,T b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T>T mmin(T a,T b){return a<b?a:b;}
template<class T>T mmax(T a,T b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
#define min mmin
#define max mmax
#define abs aabs
int a[1024][1024];
int main(){
#ifdef cnyali_lk
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int n,m,xa,ya,xb,yb;
    scanf_s("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        scanf_s("%d%d%d%d",&xa,&ya,&xb,&yb);
        ++a[xa][ya];
        --a[xb+1][ya];
        --a[xa][yb+1];
        ++a[xb+1][yb+1];
    }
    for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)printf("%d%c",a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1],j==n?'\n':' ');
    return 0;
}

