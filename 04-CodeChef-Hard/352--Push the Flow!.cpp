#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
const int maxn = 3e5 + 50,maxm = 2e5 + 50,maxk = 1e5 + 50;
const long long inf = 1e18;
int n,m,q,x,y,z,cnt = 1,tot,top,last[maxk],vis[maxk],ins[maxk],stk[maxn],id[maxm],U[maxm],V[maxm],w[maxm],fa[maxn],rev[maxn],son[maxn][2];
long long val[maxn],mn[maxn],tag[maxn];
set <pair<long long,int> > s[maxk];
struct Edge{
	int v,nxt;
}e[2 * maxm];
int read(){
	int x = 0;
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + (c ^ 48),c = getchar();
	return x;
}
inline void insert(int u,int v){
	e[++cnt] = {v,last[u]},last[u] = cnt;
}
inline void update(int u){
	mn[u] = min(val[u],min(mn[son[u][0]],mn[son[u][1]]));
}
inline bool nroot(int u){
	return son[fa[u]][0] == u || son[fa[u]][1] == u;
}
inline void reverse(int u){
	if(!u) return;
	rev[u] ^= 1;
	swap(son[u][0],son[u][1]);
}
void push_down(int u){
	if(rev[u]){
		reverse(son[u][0]);
		reverse(son[u][1]);
		rev[u] = 0;
	}
	if(tag[u]){
		val[son[u][0]] += tag[u],mn[son[u][0]] += tag[u],tag[son[u][0]] += tag[u];
		val[son[u][1]] += tag[u],mn[son[u][1]] += tag[u],tag[son[u][1]] += tag[u];
		tag[u] = 0;
	}
}
void rotate(int u){
	int v = fa[u],d = son[v][1] == u;
	if(nroot(v)) son[fa[v]][son[fa[v]][1] == v] = u;
	son[v][d] = son[u][d ^ 1],son[u][d ^ 1] = v;
	fa[u] = fa[v],fa[v] = u,fa[son[v][d]] = v;
	update(v),update(u);
}
void splay(int u){
	int t = u;
	stk[top = 1] = t;
	while(nroot(t)) t = fa[t],stk[++top] = t;
	while(top) push_down(stk[top --]);
	while(nroot(u)){
		int f = fa[u];
		if(!nroot(f)){
			rotate(u);
			break;
		}
		if((son[fa[f]][1] == f) == (son[f][1] == u)) rotate(f),rotate(u);
		else rotate(u),rotate(u);
	}
}
void access(int u){
	int v = 0;
	while(u){
		splay(u);
		son[u][1] = v;
		update(u);
		v = u,u = fa[u];
	}
}
void change_root(int u){
	access(u);
	splay(u);
	rev[u] ^= 1;
	swap(son[u][0],son[u][1]);
}
void split(int u,int v){
	change_root(u);
	access(v);
	splay(v);
}
void link(int u,int v){
	change_root(u);
	fa[u] = v;
}
void cut(int u,int v){
	split(u,v);
	fa[u] = son[v][0] = 0;
	update(v);
}
void add(int u,int v,int k){
	split(u,v);
	val[v] += k,mn[v] += k,tag[v] += k;
}
void change(int k,int c){
	if(!id[k]){//不在环上
		access(k),splay(k);
		val[k] = w[k] = c;
		update(k);
		return;
	}
	int t = s[id[k]].begin()->second;
	add(U[t],V[t],-w[t]);
	s[id[k]].erase({w[k],k});
	s[id[k]].insert({c,k});
	access(k),splay(k);
	val[k] = w[k] = c;
	update(k);
	int p = s[id[k]].begin()->second;
	if(p != t){
		cut(p,U[p]),cut(p,V[p]);
		link(t,U[t]),link(t,V[t]);
	}
	add(U[p],V[p],w[p]);
}
inline void solve(int u,int v){
	split(u,v);
	printf("%lld\n",mn[v]);
}
void dfs(int u,int fa){
	vis[u] = 1,ins[u] = 1;
	for(int i = last[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(v == fa) continue;
		if(!vis[v]){
			stk[++top] = i;
			dfs(v,u);
			top --;
		}else if(ins[v]){
			tot ++,id[i >> 1] = tot;
			for(int j = top; e[stk[j + 1] ^ 1].v != v; j --) id[stk[j] >> 1] = tot;
			//注意这里不能退栈，我因为这个调了很久
		}
	}
	ins[u] = 0;
}
int main(){
	n = read(),m = read(),mn[0] = inf;
	for(int i = 1; i <= n; i ++) val[i + m] = mn[i + m] = inf;
	for(int i = 1; i <= m; i ++){
		U[i] = read(),V[i] = read(),w[i] = read();
		insert(U[i],V[i]),insert(V[i],U[i]);
		U[i] += m,V[i] += m,val[i] = mn[i] = w[i];
	}
	dfs(1,0);
	for(int i = 1; i <= m; i ++) if(id[i]) s[id[i]].insert({w[i],i});
	for(int i = 1; i <= m; i ++) if(!id[i] || i != s[id[i]].begin()->second) link(U[i],i),link(i,V[i]);
	//若不是最小边或不在换上就加边
	for(int i = 1; i <= m; i ++) if(id[i] && i == s[id[i]].begin()->second) add(U[i],V[i],w[i]);
	//给环上剩余边加上最小值的贡献
	q = read();
	while(q --){
		z = read(),x = read(),y = read();
		if(z == 0) solve(x + m,y + m);
		else change(x,y);
	}
	return 0;
}