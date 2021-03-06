#include <cstdio>
        #include <cstdlib>
        #include <cstring>
        #include <algorithm>
        using namespace std;
        int n,m,e,ans,du[2000];
        char ch[1000][1000];
        int b[2000][1000],c[1000][1000],d[1000][1000];
        void addedge(int x,int y) {c[x][++c[x][0]]=y,du[x]++,du[y]++;}
        void edmonds(int x,int c1,int c2)
        {
        if (!b[x][c1]) {
        b[x][c1]=b[x][c2],b[x][c2]=0;
        return ;
        }
        edmonds(b[x][c1],c2,c1);
        e=b[x][c2],b[x][c2]=b[x][c1],b[x][c1]=e;
        }
        void init()
        {
        int i,j,l,k,p;
        scanf("%d%d\n",&n,&m);
        memset(b,0,sizeof(b));
        memset(d,0,sizeof(d));
        memset(du,0,sizeof(du));
        for (i=1;i<=n;i++) c[i][0]=0;
        for (i=1;i<=n;i++) {
        scanf("%s\n",ch[i]+1);
        for (j=1;j<=m;j++)
        if (ch[i][j]=='1') addedge(i,j+n);
        }
        ans=0;
        for (i=1;i<=n+m;i++) ans=max(ans,du[i]);
        for (i=1;i<=min(n,ans);i++)
        for (j=1;j<=min(m,ans);j++)
        if (ch[i][j]=='1') {
        k=(i+j-1)%ans;
        if (!k) k=ans;
        b[i][k]=j+n,b[j+n][k]=i;
        }
        for (i=1;i<=n;i++) {
        for (p=1;p<=ans && b[i][p];p++) ;
        for (j=1;j<=c[i][0];j++) {
        k=c[i][j];
        if (i<=ans && k-n<=ans) continue;
        for (;p<=ans && b[i][p];p++) ;
        for (l=1;l<=ans;l++) {
        if (b[k][l]) continue;
        edmonds(k,p,l);
        b[i][p]=k,b[k][p]=i;
        break;
        }
        }
        }
        for (i=1;i<=n;i++)
        for (j=1;j<=ans;j++)
        if (b[i][j]>n) d[i][b[i][j]-n]=j;
        printf("%d\n",ans);
        for (i=1;i<=n;i++) {
        for (j=1;j<=m;j++) printf("%d ",d[i][j]);
        printf("\n");
        }
        printf("\n");
        scanf("\n");
        }
        int main()
        {
        int t=0;
        scanf("%d\n",&t);
        scanf("\n");
        for (;t;t--) init();
        return 0;
        }