#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=100005,S=N*200,mod=1e9+9;
struct Gragh{
    static const int M=N*2;
    int cnt,y[M],nxt[M],fst[N];
    void clear(){cnt=0;memset(fst,0,sizeof fst);}
    void add(int a,int b){y[++cnt]=b,nxt[cnt]=fst[a],fst[a]=cnt;}
}g;
int Pow(int x,int y){
    int ans=1;
    for (;y;y>>=1,x=1LL*x*x%mod)
        if (y&1)
            ans=1LL*ans*x%mod;
    return 0;
}
int n,m,V=276601605,V1=691504013,V2=308495997;
int Pow1[N],Pow2[N],Sum1[N],Sum2[N];
int size[N],depth[N],son[N],fa[N][20],in[N],out[N],top[N],p[N],ap[N],Time=0,cnp=0;
void Get_Gen_Info(int x,int pre,int d){
    size[x]=1,son[x]=-1,depth[x]=d,fa[x][0]=pre;
    for (int i=1;i<20;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int i=g.fst[x];i;i=g.nxt[i])
        if (g.y[i]!=pre){
            int y=g.y[i];
            Get_Gen_Info(y,x,d+1);
            size[x]+=size[y];
            if (son[x]==-1||size[y]>size[son[x]])
                son[x]=y;
        }
}
void Get_Top(int x,int Top){
    in[x]=++Time,ap[p[x]=++cnp]=x,top[x]=Top;
    if (son[x]!=-1)
        Get_Top(son[x],Top);
    for (int i=g.fst[x];i;i=g.nxt[i]){
        int y=g.y[i];
        if (y!=son[x]&&y!=fa[x][0])
            Get_Top(y,y);
    }
    out[x]=Time;
}
struct Seg{
    int sum,L1,L2,R1,R2,ls,rs,len;
    int TagV(){return (1LL*(L1+R1)*Sum1[len-1]-1LL*(L2+R2)*Sum2[len-1]+sum)%mod;}
}T[S];
int root[N],tot=0;
int build(int L,int R){
    int rt=++tot;
    T[rt].len=R-L+1;
    if (L==R)
        return rt;
    int mid=(L+R)>>1;
    T[rt].ls=build(L,mid);
    T[rt].rs=build(mid+1,R);
    return rt;
}
void update(int prt,int &rt,int L,int R,int xL,int xR,int type,int Lv,int Rv){
    if (rt==0)
        rt=prt;
    if (L>xR||R<xL)
        return;
    if (rt==prt)
        T[rt=++tot]=T[prt];
    if (xL<=L&&R<=xR){
        if (type==0)
            T[rt].L1=(T[rt].L1+Pow1[Lv])%mod,T[rt].L2=(T[rt].L2+Pow2[Lv])%mod;
        else
            T[rt].R1=(T[rt].R1+Pow1[Rv])%mod,T[rt].R2=(T[rt].R2+Pow2[Rv])%mod;
        return;
    }
    int mid=(L+R)>>1,lenL=mid-L+1,lenR=R-mid;
    update(T[prt].ls,T[rt].ls,L,mid,xL,xR,type,Lv,Rv+lenR);
    update(T[prt].rs,T[rt].rs,mid+1,R,xL,xR,type,Lv+lenL,Rv);
    T[rt].sum=(T[T[rt].ls].TagV()+T[T[rt].rs].TagV())%mod;
}
int query(int rt,int L,int R,int xL,int xR,int L1,int L2,int R1,int R2){
    if (L>xR||R<xL)
        return 0;
    L1=(L1+T[rt].L1)%mod,L2=(L2+T[rt].L2)%mod;
    R1=(R1+T[rt].R1)%mod,R2=(R2+T[rt].R2)%mod;
    if (xL<=L&&R<=xR){
        int res=T[rt].sum;
        res=(1LL*(L1+R1)*Sum1[T[rt].len-1]-1LL*(L2+R2)*Sum2[T[rt].len-1]+res)%mod;
        res=(res+mod)%mod;
        return res;
    }
    int mid=(L+R)>>1,lenL=mid-L+1,lenR=R-mid;
    return (query(T[rt].ls,L,mid,xL,xR,L1,L2,1LL*R1*Pow1[lenR]%mod,1LL*R2*Pow2[lenR]%mod)
        +query(T[rt].rs,mid+1,R,xL,xR,1LL*L1*Pow1[lenL]%mod,1LL*L2*Pow2[lenL]%mod,R1,R2))%mod;
}
int LCA(int x,int y){
    if (depth[x]<depth[y])
        swap(x,y);
    for (int i=19;i>=0;i--)
        if (depth[x]-(1<<i)>=depth[y])
            x=fa[x][i];
    if (x==y)
        return x;
    for (int i=19;i>=0;i--)
        if (fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void Tupdate(int prt,int &rt,int x,int y){
    int Fx=top[x],Fy=top[y],Tx=0,Ty=0;
    int lca=LCA(x,y),len=depth[x]+depth[y]-depth[lca]*2+1;
    while (Fx!=Fy)
        if (depth[Fx]>depth[Fy]){
            update(prt,rt,1,n,p[Fx],p[x],1,0,Tx+1-(n-p[x]));
            Tx+=depth[x]-depth[Fx]+1;
            x=fa[Fx][0],Fx=top[x];
        }
        else {
            Ty+=depth[y]-depth[Fy]+1;
            update(prt,rt,1,n,p[Fy],p[y],0,len-Ty+1-(p[Fy]-1),0);
            y=fa[Fy][0],Fy=top[y];
        }
    if (depth[x]<depth[y])
        update(prt,rt,1,n,p[x],p[y],0,Tx+1-(p[x]-1),0);
    else
        update(prt,rt,1,n,p[y],p[x],1,0,Tx+1-(n-p[x]));
}
int Tquery(int rt,int x,int y){
    int Fx=top[x],Fy=top[y];
    int ans=0;
    while (Fx!=Fy){
        if (depth[Fx]<depth[Fy])
            swap(x,y),swap(Fx,Fy);
        ans=(ans+query(rt,1,n,p[Fx],p[x],0,0,0,0))%mod;
        x=fa[Fx][0],Fx=top[x];
    }
    if (depth[x]>depth[y])
        swap(x,y);
    ans=(ans+query(rt,1,n,p[x],p[y],0,0,0,0))%mod;
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    Pow1[0]=Pow2[0]=1,Sum1[0]=Sum2[0]=1;
    for (int i=1;i<=n;i++){
        Pow1[i]=1LL*Pow1[i-1]*V1%mod,Sum1[i]=(Sum1[i-1]+Pow1[i])%mod;
        Pow2[i]=1LL*Pow2[i-1]*V2%mod,Sum2[i]=(Sum2[i-1]+Pow2[i])%mod;
    }
    g.clear();
    for (int i=1,a,b;i<n;i++){
        scanf("%d%d",&a,&b);
        g.add(a,b);
        g.add(b,a);
    }
    Get_Gen_Info(1,0,0);
    Get_Top(1,1);
    memset(T,0,sizeof T);
    root[0]=build(1,n);
    int LASTANS=0;
    for (int i=1;i<=m;i++){
        char opt[5];
        int x,y;
        scanf("%s%d",opt+1,&x);
        x^=LASTANS;
        root[i]=root[i-1];
        if (opt[1]=='A'){
            scanf("%d",&y);
            Tupdate(root[i-1],root[i],x,y);
        }
        if (opt[1]=='R')
            root[i]=root[x];
        if (opt[1]=='Q'&&opt[2]=='S'){
            scanf("%d",&y);
            if (x==y){
                LASTANS=query(root[i],1,n,1,n,0,0,0,0);
                LASTANS=(1LL*LASTANS*V%mod+mod)%mod;
                printf("%d\n",LASTANS);
            }
            else if (in[y]<=in[x]&&out[x]<=out[y]){
                for (int j=19;j>=0;j--)
                    if (depth[x]-(1<<j)>depth[y])
                        x=fa[x][j];
                LASTANS=query(root[i],1,n,1,n,0,0,0,0)-query(root[i],1,n,in[x],out[x],0,0,0,0);
                LASTANS=(1LL*LASTANS*V%mod+mod)%mod;
                printf("%d\n",LASTANS);
            }
            else {
                LASTANS=query(root[i],1,n,in[y],out[y],0,0,0,0);
                LASTANS=(1LL*LASTANS*V%mod+mod)%mod;
                printf("%d\n",LASTANS);
            }
        }
        if (opt[1]=='Q'&&opt[2]=='C'){
            scanf("%d",&y);
            LASTANS=Tquery(root[i],x,y);
            LASTANS=(1LL*LASTANS*V%mod+mod)%mod;
            printf("%d\n",LASTANS);
        }
    }
    return 0;
}