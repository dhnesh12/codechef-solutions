#include<bits/stdc++.h>
typedef int LL;
#define pb push_back
#define pii std::pair<LL,LL>
const LL maxn=2e3+9,mod=998244353;
LL add(LL x,LL y){
	x+=y; return x>=mod?x-mod:x;
}
LL dec(LL x,LL y){
	x-=y; return x<0?x+mod:x;
}
LL mul(LL x,LL y){
	return 1ll*x*y%mod;
}
void Chkmin(LL &x,LL y){
	if(y<x) x=y;
}
void Chkmax(LL &x,LL y){
	if(y>x) x=y;
}
LL Pow(LL base,LL b){
	LL ret(1); while(b){
		if(b&1) ret=mul(ret,base);
		base=mul(base,base); b>>=1;
	}return ret;
}
namespace Uf{
	LL fa[maxn],size[maxn];
	void Init(LL N){
		for(LL i=1;i<=N;++i) fa[i]=i,size[i]=1;
	}
	LL Find(LL x){
		return fa[x]==x?x:fa[x]=Find(fa[x]);
	}
	void Merge(LL x,LL y){
		x=Find(x); y=Find(y);
		if(x==y) return;
		fa[x]=y;
		size[y]+=size[x];
	}
}
struct Gragh{
	LL nod;
	std::vector<LL> V[maxn];
	void Clear(){
		//for(LL i=1;i<=20;++i) std::vector<LL>().swap(V[i]);
		for(LL i=0;i<=nod;++i) std::vector<LL>().swap(V[i]);
		nod=0;
	}
	void Add(LL u,LL v){
		V[u].pb(v); V[v].pb(u);
	}
}G1,G2;
LL T,n;
LL f[maxn],g[maxn];
LL none[maxn],chosen[maxn][maxn];
std::vector<LL> Set[maxn];
char s[maxn];
void Build1(){
	static LL d[maxn][maxn],d2[maxn][maxn],pos[maxn];
	//memset(d,0,sizeof(d)); memset(d2,0,sizeof(d2)); memset(pos,0,sizeof(pos));
	Uf::Init(n);
	for(LL i=1;i<=n;++i){
		for(LL j=1;j<=n;++j){
			d[i][j]=d2[i][j]=0;
		}
	}
	for(LL mid=1;mid<=n;++mid){
		for(LL len=2;len<=std::min(n-mid+1,mid);++len){
			if(s[mid-len+1]==s[mid+len-1]){
				//printf("(%d,%d)\n",mid-len+1,mid+len-1);
				Uf::Merge(mid-len+1,mid+len-1);
			}else{
				d[mid-len+1][mid+len-1]=1;
				break;
		    }
		}
	}
	for(LL mid=1;mid<n;++mid){
		for(LL len=1;len<=std::min(n-mid+1,mid);++len){
			if(s[mid-len+1]==s[mid+len]){
				Uf::Merge(mid-len+1,mid+len);
			}else{
				d[mid-len+1][mid+len]=1;
				break;
		    }
		}
	}
	for(LL i=1;i<=n;++i){
		if(Uf::Find(i)==i){
			//printf("# %d,%d\n",i,Uf::size[i]);//
			pos[i]=++G1.nod;
			f[G1.nod]=dec(Pow(2,Uf::size[i]),1);
			g[G1.nod]=Pow(f[G1.nod],mod-2);
		}
	}
	//printf("# %d\n",G1.nod);//
	for(LL i=1;i<=n;++i){
		for(LL j=i+1;j<=n;++j)if(d[i][j]){
			LL x(Uf::Find(i)),y(Uf::Find(j));
			x=pos[x]; y=pos[y];
			if(x>y) std::swap(x,y);
			if(x==y) continue;
			if(d2[x][y]) continue;
			d2[x][y]=1;
			G1.Add(x,y);
			//printf("(%d,%d)%d,%d\n",i,j,x,y);//
		}
	}
	//for(LL i=1;i<=G1.nod;++i) printf("%d ",f[i]); puts("");
}
void Build2(){
	static LL lev[maxn],mark[maxn],d[maxn],pos[maxn],last[maxn],bel[maxn];
    static std::set<pii> St;
	static std::vector<LL> M[maxn];
	/*{
		//G1.nod=0; 
		G2.nod=0;
		St.clear(); 
		memset(lev,0,sizeof(lev));
		memset(mark,0,sizeof(mark));
		memset(d,0,sizeof(d));
		memset(pos,0,sizeof(pos));
		memset(last,0,sizeof(last));
		memset(bel,0,sizeof(bel));
		//memset(mark,0,sizeof(mark));
	}*/
	for(LL i=1;i<=G1.nod;++i) lev[i]=mark[i]=d[i]=last[i]=0;
	for(LL i=1;i<=G1.nod;++i) std::vector<LL>().swap(M[i]);
	for(LL i=1;i<=G1.nod;++i){
		St.insert(pii(0,i));
	}
	lev[0]=-1;
	LL pre(G1.nod);
	for(LL tim=1;tim<=G1.nod;++tim){
		LL u(St.begin()->second); St.erase(St.begin());
		//printf("%d ",u);
		mark[u]=1;
		//printf("(%d,%d)\n",lev[u],pre);
		if(lev[u]<=pre){
			++G2.nod;
			std::vector<LL> Tmp(M[u]);
			Tmp.pb(u);
			Set[G2.nod]=Tmp;
			//if(u==4){
			//	for(LL i=0;i<M[u].size();++i) printf("%d ",M[u][i]); puts("");
			//}
			//printf("(%d)%d,%d\n",u,G2.nod,bel[last[u]]);
			//printf("%d,%d\n",bel[last[u]],Tmp.size());
			G2.Add(G2.nod,bel[last[u]]);
		}else{
			Set[G2.nod].pb(u);
		}
		mark[u]=1;
		for(LL i=0;i<G1.V[u].size();++i){
			LL v(G1.V[u][i]); if(mark[v]) continue;
			M[v].pb(u);
			//if(v==4) printf("(%d)\n",u);
			St.erase(pii(-lev[v],v));
			++lev[v];
			last[v]=u;
			St.insert(pii(-lev[v],v));
		}
		pre=lev[u];
		bel[u]=G2.nod;
	}
	//for(LL i=1;i<=G2.nod;++i){
	//	for(LL j=0;j<Set[i].size();++j) printf("%d ",Set[i][j]); puts("");
	//}
	//puts("");
	//printf("# %d\n",G2.nod);
}
void Dfs(LL u,LL fa){
	//printf("# %d,%d\n",u,fa);
	static LL mark[maxn],inv[maxn];
	for(LL i=0;i<G2.V[u].size();++i){
		LL v(G2.V[u][i]); if(v==fa) continue;
		//printf("(%d,%d)\n",v,u);
		Dfs(v,u);
	}
	none[u]=1;
	//printf("(%d,%d)\n",u,fa);
	//memset(mark,0,sizeof(mark));//
	for(LL i=0;i<Set[u].size();++i) mark[Set[u][i]]=1;
	//memset(inv,0,sizeof(inv));//
	for(LL i=0;i<G2.V[u].size();++i){
		LL v(G2.V[u][i]); if(v==fa) continue;
		LL Tmp(none[v]);
		for(LL j=0;j<Set[v].size();++j) if(!mark[Set[v][j]]){
			Tmp=add(Tmp,chosen[v][Set[v][j]]);
		}
		inv[v]=Pow(Tmp,mod-2);
		none[u]=mul(none[u],Tmp);
	}
	static std::vector<LL> P,Q;
	std::vector<LL>().swap(P);
	std::vector<LL>().swap(Q);
	for(LL i=0;i<G2.V[u].size();++i){
		LL v(G2.V[u][i]); if(v==fa) continue;
		for(LL j=0;j<Set[v].size();++j) mark[Set[v][j]]=0;
	}
	for(LL i=0;i<Set[u].size();++i){
		LL x(Set[u][i]);
		if(mark[x]) P.pb(x);
		else Q.pb(x);
	}
	for(LL i=0;i<P.size();++i){
		LL x(P[i]);
		chosen[u][x]=mul(none[u],f[x]);
	}
	//printf("(%d:%d,%d)\n",u,P.size(),Q.size());
	if(u==1){
		//printf("#:");
		//for(LL i=0;i<P.size();++i) printf("%d ",P[i]); puts("");
		//printf("#:");
		//for(LL i=0;i<Q.size();++i) printf("%d ",Q[i]); puts("");
	}
	for(LL i=0;i<Q.size();++i){
		chosen[u][Q[i]]=mul(none[u],f[Q[i]]);
	}
	for(LL i=0;i<Set[u].size();++i) mark[Set[u][i]]=1;
	for(LL i=0;i<Q.size();++i) mark[Q[i]]=1;
	for(LL i=0;i<G2.V[u].size();++i){
		LL v(G2.V[u][i]); if(v==fa) continue;
		for(LL j=0;j<Set[v].size();++j){
			LL x(Set[v][j]); if(!mark[x]) continue;
			chosen[u][x]=mul(chosen[u][x],inv[v]);
			chosen[u][x]=mul(chosen[u][x],1ll*chosen[v][x]*g[x]%mod);
		}
	}
	for(LL i=0;i<Set[u].size();++i) mark[Set[u][i]]=0;
	//printf("%d: %d\n",u,none[u]);
	//for(LL i=0;i<Set[u].size();++i) printf("(%d,%d) ",Set[u][i],chosen[u][Set[u][i]]); puts("");
}
void Solve(){
	//memset(chosen,0,sizeof(chosen));
	//memset(none,0,sizeof(none));
	//for(LL i=0;i<=10;++i) printf("%d ",G2.V[i].size()); puts("");
	Dfs(0,-1);
	//puts("----------");
	LL ret(none[0]);
	//freopen("x.txt","w",stdout);
	printf("%d\n",ret);
}
void Clear(){
	for(LL i=1;i<=std::max(G1.nod,G2.nod);++i){
		std::vector<LL>().swap(Set[i]);
	}
	G1.Clear(); G2.Clear();
	for(LL i=1;i<=n;++i){
		std::vector<LL>().swap(Set[i]);
	}
}
int main(){
	//freopen("y1.txt","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf(" %s",s+1);
		n=strlen(s+1);
		Build1();
		//puts("-----------");
		Build2();
		//puts("-----------");
		Solve();
		//puts("");
		Clear();
	}
}