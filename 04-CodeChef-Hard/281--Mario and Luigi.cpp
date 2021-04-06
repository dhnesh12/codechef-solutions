#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint unsigned
#define db long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define IT iterator
 
#define PB push_back
#define MK make_pair
#define LB lower_bound
#define UB upper_bound
#define EB emplace_back
#define fi first
#define se second
 
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define UPD(x,y) (((x)+=(y))>=mo?x-=mo:233)
#define CLR(a,v) memset(a,v,sizeof(a));
#define CPY(a,b) memcpy(a,b,sizeof(a));
 
#define LS3 k*2,l,mid
#define RS3 k*2+1,mid+1,r
#define LS5 k*2,l,mid,x,y
#define RS5 k*2+1,mid+1,r,x,y
#define GET pushdown(k);int mid=(l+r)/2
 
#define inf 2000000000
#define sqr(x) ((x)*(x))
using namespace std;
const int N=200005;
int sz[N*4],x[N],y[N],v[N],n,m;
ll q[N],S[N],del[N*4];
void build(int k,int l,int r){
	del[k]=sz[k]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
}
void change(int k,int l,int r,int p,int v){
	if (l==r){
		sz[k]+=v;
		del[k]=(sz[k]&1?q[l]:0);
		return;
	}
	int mid=(l+r)/2;
	if (p<=mid) change(k*2,l,mid,p,v);
	else change(k*2+1,mid+1,r,p,v);
	sz[k]=sz[k*2]+sz[k*2+1];
	del[k]=del[k*2+1]+(sz[k*2+1]&1?-del[k*2]:del[k*2]);
}
int find(ll x){
	return lower_bound(q+1,q+*q+1,x)-q;
}
void solve(){
	*q=0;
	scanf("%d%d",&n,&m);
	For(i,1,n) S[i]=0;
	For(i,1,m){
		scanf("%d%d%d",&x[i],&y[i],&v[i]);
		q[++*q]=(S[x[i]]+=v[i]);
		q[++*q]=(S[y[i]]+=v[i]);
	}
	sort(q+1,q+*q+1);
	//*q=unique(q+1,q+*q+1)-q-1;
	build(1,1,*q);
	For(i,1,n) S[i]=0;
	For(i,1,m){
		if (S[x[i]]) change(1,1,*q,find(S[x[i]]),-1);
		change(1,1,*q,find(S[x[i]]+=v[i]),1);
		if (S[y[i]]) change(1,1,*q,find(S[y[i]]),-1);
		change(1,1,*q,find(S[y[i]]+=v[i]),1);
		printf("%lld\n",del[1]/2);
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}