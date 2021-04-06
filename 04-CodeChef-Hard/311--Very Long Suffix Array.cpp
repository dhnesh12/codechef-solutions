#include <bits/stdc++.h>
#define Ls tr[x].ls
#define Rs tr[x].rs
using namespace std;
const int N=1e6+50,mo=1e9+7;
int gi(){
    char ch=getchar(); int x=0,q=0;
    while(ch<'0'||ch>'9') q=ch=='-'?1:q,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return q?-x:x;
}
struct data{
    int ls,rs,R,l,r,op,siz,fa;
}tr[N];
struct date{
    int l,r,op,x;
    bool operator < (const date &c) const {
	return l<c.l;
    }
}w[N];
int n,m,rev[N],tot,rt=1,top,tim,rk[N];
int fap(int x,int y){
    int s=1;
    for (; y; y>>=1,x=1ll*x*x%mo)
	if (y&1) s=1ll*s*x%mo;
    return s;
}
void pushd(int x){
    rev[Ls]^=1,rev[Rs]^=1;
    tr[Ls].op^=1,tr[Rs].op^=1;
    swap(Ls,Rs),rev[x]=0;
    return;
}
void update(int x){
    tr[x].siz=tr[Ls].siz+tr[Rs].siz+tr[x].r-tr[x].l+1;
    tr[Ls].fa=x,tr[Rs].fa=x;
    return;
}
data split(int x,int k){
    if (!x) return (data){0,0};
    if (rev[x]) pushd(x);
    data t; tr[x].fa=0;
    if (tr[Ls].siz+tr[x].r-tr[x].l+1<=k){
	t=split(Rs,k-tr[Ls].siz-tr[x].r+tr[x].l-1);
	tr[x].rs=t.ls,t.ls=x;
    }
    else if (tr[Ls].siz>=k){
	t=split(Ls,k);
	tr[x].ls=t.rs,t.rs=x;
    }
    else{
	++tot,k-=tr[Ls].siz;
	if (tr[x].op==0){
	    tr[tot]=(data){0,tr[x].rs,rand(),tr[x].l+k,tr[x].r,0};
	    tr[x]=(data){tr[x].ls,0,rand(),tr[x].l,tr[x].l+k-1,0};
	}
	else{
	    tr[tot]=(data){0,tr[x].rs,rand(),tr[x].l,tr[x].r-k,1};
	    tr[x]=(data){tr[x].ls,0,rand(),tr[x].r-k+1,tr[x].r,1};
	}
	t.ls=x,t.rs=tot,update(tot);
    }
    return update(x),t;
}
int merge(int x,int y){
    if (!x||!y) return x+y;
    if (rev[x]) pushd(x);
    if (rev[y]) pushd(y);
    if (tr[x].R<tr[y].R){
	tr[x].rs=merge(tr[x].rs,y);
	return update(x),x;
    }
    tr[y].ls=merge(x,tr[y].ls);
    return update(y),y;
}
void dfs(int x){
    if (!x) return;
    if (rev[x]) pushd(x);
    dfs(tr[x].ls);
    rk[x]=tim+1,tim+=tr[x].r-tr[x].l+1;
    w[++top]=(date){tr[x].l,tr[x].r,tr[x].op,x};
    dfs(tr[x].rs);
    return;
}
int querypre(int x){
    if (!tr[x].ls){
	while(x){
	    if (tr[tr[x].fa].rs==x){
		x=tr[x].fa; break;
	    }
	    x=tr[x].fa;
	}
    }
    else{
	x=tr[x].ls;
	while(tr[x].rs) x=tr[x].rs;
    }
    if (tr[x].op) return tr[x].l;
    return tr[x].r;
}
int query(int x){
    if (x>n) return 0;
    int l=1,r=top,mid;
    while(l<=r){
	mid=(l+r)>>1;
	if (w[mid].l<=x){
	    if (w[mid].r>=x){
		if (w[mid].op)
		    return rk[w[mid].x]+w[mid].r-x;
		return rk[w[mid].x]+x-w[mid].l;
	    }
	    l=mid+1;
	}
	else r=mid-1;
    }
}
int main(){
    srand(19260817);
    cin>>n>>m; int op,u,v;
    data x,y;
    tr[++tot]=(data){0,0,rand(),1,n,0,n};
    for (int i=1; i<=m; ++i){
	op=gi(),u=gi(),v=gi();
	if (op){
	    x=split(rt,u-1);
	    y=split(x.rs,v-u+1);
	    rev[y.ls]^=1,tr[y.ls].op^=1;
	    rt=merge(x.ls,merge(y.ls,y.rs));
	}
	else{
	    x=split(rt,u-1);
	    y=split(x.rs,v-u+1);
	    rt=merge(y.ls,merge(x.ls,y.rs));
	}
    }
    dfs(rt);
    sort(w+1,w+top+1);
    int ans=0;
    for (int i=1; i<=top; ++i){
	if (w[i].l==w[i].r){
	    if (rk[w[i].x]>1&&query(querypre(w[i].x)+1)<query(w[i].l+1)) ++ans;
	    continue;
	}
	ans+=w[i].r-w[i].l-1;
	if (!w[i].op){
	    if (rk[w[i].x]>1&&query(querypre(w[i].x)+1)<rk[w[i].x]+1) ++ans;
	    if (rk[w[i].x]+w[i].r-w[i].l<query(w[i].r+1)) ++ans;
	}
	else{
	    if (rk[w[i].x]>1&&query(querypre(w[i].x)+1)<query(w[i].r+1)) ++ans;
	    if (query(w[i].r+1)<rk[w[i].x]) ++ans;
	}
    }
    cout<<fap(2,ans);
    return 0;
}