#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=10010;
const int M=110;
struct node{int x,y,z;}p[N];
int T,n,tot,cnt,fa[M],g[M][M];
ll ans;
bool cmp(const node &a,const node &b) {return a.z<b.z;}
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
int main() {
    int i,j,fx,fy;
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        tot=ans=cnt=0;
        for (i=1;i<=n;i++) fa[i]=i;
        for (i=1;i<=n;i++) {
            for (j=1;j<=n;j++) {
                scanf("%d",&g[i][j]);
                if (g[i][j]) {
                    ++tot;
                    p[tot].x=i;
                    p[tot].y=j;
                    p[tot].z=g[i][j];
                }
            }
        } sort(p+1,p+1+tot,cmp);
        for (i=1;i<=tot;i++) {
            fx=find(p[i].x);
            fy=find(p[i].y);
            if (fx==fy) continue;
            fa[fx]=fy; cnt++;
            ans+=p[i].z;
        }
        if (n==1&&g[1][1]) printf("%d\n",g[1][1]);
        else if (n!=1&&n==cnt+1) printf("%lld\n",ans<<1ll);
        else puts("-1");
    } return 0;
}
