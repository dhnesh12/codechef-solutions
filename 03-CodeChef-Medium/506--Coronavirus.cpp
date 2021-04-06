#pragma GCC optimize("Ofast,unroll-loops,fast-math")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll ;
#define pll pair<ll , ll >
#define all(x) (x).begin(),(x).end()
#define sz(x) (ll)(x).size()
#define X   first
#define Y   second
#define mp  make_pair
#define pii pair<int , int>
#define vec vector
#define file_io freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#define migmig ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define pb push_back
ll poww(ll a, ll b, ll md) {
    return (!b ? 1 : (b & 1 ? a * poww(a * a % md, b / 2, md) % md : poww(a * a % md, b / 2, md) % md));
}
const int maxn = 1000*100+5 ;
const ll inf = 9223372036854775807 ;
const ll mod = 1e9 + 7 ;
const int lg = 18 ; 
int n , lazy[4 * maxn] , par[lg][maxn]  , mark[maxn] , h[maxn] , st[maxn] , ft[maxn]  , cnt , sh[4 * maxn] ; 
vec<int> t  , adj[maxn]; 
pii seg[4 * maxn] , node[4 * maxn] ; 
void dfs(int v){
	mark[v] = 1 ; 
	st[v] = sz(t) ; 
	t.pb(v) ; 
	for(auto u : adj[v]){
		if(!mark[u]){
			h[u] = h[v] + 1 ; 
			par[0][u] = v ; 
			for(int i = 1 ; i < lg ; i ++ ){
				par[i][u] = par[i-1][par[i-1][u]] ; 
			}		
			dfs(u); 
		}
	}
	ft[v] = sz(t) ;
}
void build(int x , int lx , int rx){
	lazy[x] = 1 ; 
	if(rx - lx == 1){
		seg[x] = {h[t[lx]] , t[lx]} ; 
		return ; 
	}
	int mid = lx + rx >> 1 ; 
	build(x << 1 , lx , mid) ; 
	build(x << 1 | 1 , mid , rx) ; 
	seg[x] = max(seg[x << 1]  , seg[x << 1 | 1]) ; 
}
inline void shift(const int &x ,const int &lx ,const int &rx){
	if(!sh[x]) return ; 
	node[x] = {seg[x].X * lazy[x] , seg[x].Y * lazy[x]} ; 
	if(rx - lx > 1){
		lazy[x << 1] = lazy[x] ; 
		lazy[x << 1 | 1] = lazy[x] ; 
		sh[x << 1] = sh[x << 1 | 1] = 1 ; 
	}
	sh[x] = 0 ; 
}
void upd(const int &l ,const int &r ,const int &v ,const int &x = 1 ,const int &lx = 0 ,const int &rx  = n){
	shift(x , lx , rx) ; 
	if(lx >= r || rx <= l) return ; 
	if(lx >= l && rx <= r){
		lazy[x] = v ; 
		sh[x] = 1 ; 
		shift(x  , lx , rx) ; 
		return ; 
	}
	int mid = lx + rx >> 1 ; 
	upd(l , r , v , x << 1 , lx , mid) ; 
	upd(l , r , v , x << 1 | 1 , mid , rx) ; 
	node[x] = max(node[x << 1] , node[x << 1 | 1]) ; 
}   
int get(int v ,const int &k ){
    for(int i = k ; i ; i -= i & -i){
    	v = par[__builtin_ctz(i)][v] ; 
	}
	return v ; 
}
int Main()
{
	scanf("%d" , &n) ; 
	for(int i = 1 ; i < n ; i ++){
		int u , v ; 
		scanf("%d%d" , &u , &v) ; 
		adj[u].pb(v) ; 
		adj[v].pb(u) ; 
	}
	h[1] = 1 ;
	for(int i = 0 ; i < lg ; i ++ ) par[i][1] = 1 ;  
	dfs(1) ; 
	build(1 , 0 , n) ; 
	int v  , ans = 0 ; 
	for(int i = 1 ; i < 4 * maxn ; i ++ ) node[i] = seg[i] ; 
	for(int i = 1 ; i <= n ; i ++ ){
		cnt = 0 ; 
		while(node[1].X){
			cnt ++ ;
			v  = get(node[1].Y , min(i , h[node[1].Y] - 1)) ; 
		//	cout<<node[1].Y << " : " << v <<" " << st[v] <<" " << ft[v] << endl ; 
			upd( st[v] , ft[v] , 0 ) ; 
			ans ++ ; 
			if(cnt > n)break ; 
		}
		//cout<<i <<":"<<ans << endl ; 
		upd(0 , n , 1) ;
	}
	printf("%d\n" , ans) ;
	for(int i = 0 ; i <= n ; i ++ ){
		adj[i].clear() ; 
		mark[i] = st[i] = ft[i] = 0 ; 
		for(int j = 0 ; j < lg ; j ++ ) par[j][i] = 0 ; 
		h[i] = 0 ; 
	}
	t.clear() ; 
	for(int i = 0 ; i <= 4 * n ; i ++ ){
		lazy[i] = 0 ; 
		seg[i] = node[i] = {0 , 0} ; 
		sh[i] = 0 ; 
	}
}

int main(){
	int q ; 
	scanf("%d" , &q); 
	while(q--){
		Main() ; 
	}
}







