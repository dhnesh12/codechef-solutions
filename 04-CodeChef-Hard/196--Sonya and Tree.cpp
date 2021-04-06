#pragma GCC optimize(2)//O2优化
#pragma GCC optimize(3,"Ofast","inline")//O3优化""""))


#include<bits/stdc++.h>
typedef int LL;
typedef double dl;
#define opt operator
#define pb push_back
#define pii std::pair<LL,LL>
const LL maxn=5e5+9,mod=998244353,inf=0x3f3f3f3f;
LL Read(){
	LL x(0),f(1); char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1; c=getchar();
	}
	while(c>='0' && c<='9'){
		x=(x<<3ll)+(x<<1ll)+c-'0'; c=getchar();
	}return x*f;
}
void Chkmin(LL &x,LL y){
	if(y<x) x=y;
}
void Chkmax(LL &x,LL y){
	if(y>x) x=y;
}
LL add(LL x,LL y){
	return x+=y,x>=mod?x-mod:x;
}
LL dec(LL x,LL y){
	return x-=y,x<0?x+mod:x;
}
LL mul(LL x,LL y){
	return 1ll*x*y%mod;
}
LL Pow(LL base,LL b){
	LL ret(1); while(b){
		if(b&1) ret=mul(ret,base); base=mul(base,base); b>>=1;
	}return ret;
}
struct node{
	pii A,B;
	void Init(){
		A=B=pii(inf,0);
	}
	void Upd(pii C){
		if(C.first<A.first){
			B=A; A=C;
		}else if(C.first==A.first){
			A.second+=C.second;
		}else if(C.first<B.first){
			B=C;
		}else if(B.first==C.first){
			B.second+=C.second;
		}
	}
	void Upd(node C){
		Upd(C.A); Upd(C.B);
	}
};
namespace Sgt{
    node tr[maxn<<2];
	LL tag[maxn<<2];
	void Update(LL nw){
		tr[nw]=tr[nw<<1];
		tr[nw].Upd(tr[nw<<1|1]);
	}
	void Pushdown(LL nw){
		LL x(tag[nw]);
		if(x){
			tag[nw]=0;
			tr[nw<<1].A.first+=x; tr[nw<<1].B.first+=x; tag[nw<<1]+=x;
			tr[nw<<1|1].A.first+=x; tr[nw<<1|1].B.first+=x; tag[nw<<1|1]+=x;
		}
	}
	void Build(LL nw,LL l,LL r){
		if(l==r){
			tr[nw].Init(); tr[nw].Upd(pii(l,1));
			return;
		}
		LL mid(l+r>>1);
		Build(nw<<1,l,mid); Build(nw<<1|1,mid+1,r);
		Update(nw);
	}
	void Modify(LL nw,LL l,LL r,LL lt,LL rt,LL v){
		if(lt<=l && rt>=r){
			tr[nw].A.first+=v; tr[nw].B.first+=v;
			tag[nw]+=v;
			return;
		}
		Pushdown(nw);
		LL mid(l+r>>1);
		if(lt<=mid) Modify(nw<<1,l,mid,lt,rt,v);
		if(rt>mid) Modify(nw<<1|1,mid+1,r,lt,rt,v);
		Update(nw);
	}
	node Query(LL nw,LL l,LL r,LL lt,LL rt){
		if(lt<=l && rt>=r) return tr[nw];
		Pushdown(nw);
		LL mid(l+r>>1);
		if(rt<=mid) return Query(nw<<1,l,mid,lt,rt);
		if(lt>mid) return Query(nw<<1|1,mid+1,r,lt,rt);
		node ret(Query(nw<<1,l,mid,lt,rt));
		node tmp(Query(nw<<1|1,mid+1,r,lt,rt));
		ret.Upd(tmp);
		return ret;
	}
}
struct edge{
	LL to,nxt;
}dis[maxn<<1];
LL n,num;
LL fa[maxn],a[maxn],key1[maxn],key2[maxn],dep[maxn],head[maxn];
std::multiset<LL> Set[maxn];
std::multiset<pii> S2;
std::multiset<LL>::iterator it1;
std::vector<LL> V[maxn];
void Add(LL u,LL v){
	dis[++num]=(edge){v,head[u]}; head[u]=num;
}
void Dfs(LL u,LL f){
	std::queue<LL> que;
	que.push(u); fa[u]=0; dep[u]=1;
	while(que.size()){
		LL u(que.front()); que.pop();
		for(LL i=head[u];i;i=dis[i].nxt){
			LL v(dis[i].to); if(dep[v]) continue;
			dep[v]=dep[u]+1; fa[v]=u;
			Set[u].insert(a[v]);
			que.push(v);
		}
	}
}
void Init(){
	n=Read();
	for(LL i=1;i<=n;++i){
		a[i]=Read(); ++a[i];
	}
	for(LL i=1;i<n;++i){
		LL x(Read()),y(Read());
		Add(x,y); Add(y,x);
	}
	Dfs(1,0);
//	puts("033");
}
void Update1(LL x){
	if(!Set[x].size()) return;
	if(key1[x]){
		LL lt(key1[x]),rt(key1[x]=std::max(a[x],*Set[x].begin()));
		if(lt^rt){
			if(lt<rt) Sgt::Modify(1,1,n,lt,rt-1,1);
			else Sgt::Modify(1,1,n,rt,lt-1,-1);
		}
		return;
	}
	key1[x]=std::max(a[x],*Set[x].begin());
	Sgt::Modify(1,1,n,key1[x],n,-1);
}
void Update2(LL x){
	if(Set[x].size()<2) return;
	if(key2[x]){
		S2.erase(S2.find(pii(key2[x],x)));
	}
	key2[x]=a[x];
	it1=Set[x].begin();
	Chkmax(key2[x],*(++it1));
    S2.insert(pii(key2[x],x));
}
void Build(){
	static LL c[maxn];
	Sgt::Build(1,1,n);
	for(LL i=1;i<=n;++i){
		Update1(i);
	}
	LL num(0);
	for(LL i=1;i<=n;++i) num+=c[i]==1;
    for(LL i=1;i<=n;++i) if(Set[i].size()>=2){
		it1=Set[i].begin();
		Chkmax(key2[i],*(++it1));
		S2.insert(pii(key2[i],i));
	}
}
// #define checktime
void Get(){
	LL ans(0);
	{
		node ret(Sgt::tr[1]);
		if(ret.A.first==1) ans+=ret.A.second;
	}
	LL lt(1),rt(n);
	if(S2.size()){
		LL x((*S2.begin()).second);
		lt=(*S2.begin()).first;
		if(fa[x]){
			rt=a[fa[x]]-1;
		}
	}
	if(lt<=rt){
		node ret(Sgt::Query(1,1,n,lt,rt));
		if(ret.A.first==2) ans+=ret.A.second;
		if(ret.B.first==2) ans+=ret.B.second;
	}
#ifndef checktime
	printf("%d\n",ans);
#endif
}

void Solve(){
	LL m(Read());
	while(m--){
		LL x(Read()),y(Read());
		if(x==y){
			Get();
			continue;
		}
		if(dep[x]<dep[y]) std::swap(x,y);
		LL fx(fa[x]),fy(fa[y]);
		LL vx(a[x]),vy(a[y]);
		static LL b[10];
		LL tot(0);
		b[++tot]=x; b[++tot]=y;
		if(fx) b[++tot]=fx;
		if(fy) b[++tot]=fy;
		tot=std::unique(b+1,b+1+tot)-b-1;
		std::swap(a[x],a[y]);
		if(fx){
			Set[fx].erase(Set[fx].find(vx)); Set[fx].insert(vy);
		}
		if(fy){
			Set[fy].erase(Set[fy].find(vy)); Set[fy].insert(vx);
		}
		for(LL i=1;i<=tot;++i){
			Update1(b[i]); 
			Update2(b[i]);
		}
		Get();
	}
}
int main(){
	Init();
	Build();
	Solve();
	return 0;
}



