#include<bits/stdc++.h>
 
#define gc getchar
#define ii(x) scanf(" %d", &x)
#define ill(x) scanf(" %lld", &x)
#define ll long long
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define fill(a,b) memset(a, b, sizeof a)
#define rep(i,a,b) for(i=a;i<b;i++)
#define per(i,a,b) for(i=a;i>=b;i--)
#define pii pair<int, int>
 
using namespace std;
 
void in(int &x){
    register int c=gc();
    x=0;
    for(;(c<48||c>57);c=gc());
    for(;c>47&&c<58;c=gc()){x=(x<<1)+(x<<3)+c-48;}
}
 
const int N = 1e4+4;
int y, z, parent[N], depth[N], maxD, height[N], radius;
std::vector<int> g[N], dia, cen;
bool vis[N];
std::queue<int> q;
 
void farthest(){
	int v;
	while(!q.empty()){
		v = q.front(); q.pop(); vis[v] = true;
		for(int u : g[v]) if(!vis[u]) q.push(u);
	}
	y = v;
}
 
void theDiameter(int v, int d){
	vis[v] = true; depth[v] = d;
	for(int u : g[v]) if(!vis[u]){
		parent[u] = v;
		theDiameter(u, d + 1);
	}
}
 
void findCenters(int n){
	int i, cur = 0;
	fill(vis, false);
	q.push(1); farthest();
	fill(vis, false); depth[y] = 0;
	theDiameter(y, 0);
	rep(i, 1, n + 1) if(depth[i] > cur){
		cur = depth[i];
		z = i;
	}
	i = z; dia.clear(); cen.clear();
	for(; i != y; i = parent[i]) dia.pb(i); dia.pb(i);
	int sz = dia.size(); radius = sz >> 1;
	cen.pb(dia[sz >> 1]);
	if(sz % 2 == 0) cen.pb(dia[(sz >> 1) - 1]);
}
 
void findHeights(int v){
	vis[v] = true;
	int h = -1;
	for(int u : g[v]) if(!vis[u]){
		findHeights(u);
		h = max(h, height[u]);
	}
	height[v] = h + 1;
}
 
int main()
{
	int t, n, i, u, v, sz;
	in(t); while(t--){
		in(n);
		rep(i, 1, n + 1){
			g[i].clear();
		}
		rep(i, 1, n){
			in(u); in(v);
			g[u].pb(v); g[v].pb(u);
		}
		if(n == 2){ printf("NO\n"); continue; }
		findCenters(n);
		fill(vis, false);
		sz = cen.size();
		if(sz & 1){
			findHeights(cen[0]);
			int cnt = 0; bool ok = true;
			for(int u : g[cen[0]]) if(height[u] == radius - 1) cnt++;
			if(cnt != 2) ok = false;
			puts(ok ? "YES" : "NO");
		}else{
			auto it = g[cen[0]].begin();
			while(*it != cen[1]) it++; g[cen[0]].erase(it);
			it = g[cen[1]].begin();
			while(*it != cen[0]) it++; g[cen[1]].erase(it);
			findHeights(cen[0]); findHeights(cen[1]);
			int cnt = 0; bool ok1 = true, ok2 = true;
			for(int u : g[cen[0]]) if(height[u] == radius - 2) cnt++;
			if(cnt > 1) ok1 = false; cnt = 0;
			for(int u : g[cen[1]]) if(height[u] == radius - 2) cnt++;
			if(cnt > 1) ok2 = false;
			puts((ok1 || ok2) ? "YES" : "NO");
		}
	}
 
	return 0;
}  