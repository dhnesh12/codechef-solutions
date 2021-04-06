#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
template <class c, class cmp = less<c> > using ordered_set = tree<c, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL); 

#define ld long double


#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...) 1
#endif
template<class T> ostream& operator<<(ostream &os, vector<T> V) {os << "[ "; for(auto v : V) os << v << " "; return os << "]";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template <typename T,typename U>pair<T,U> operator+(const pair<T,U> & l,const std::pair<T,U> & r) { return {l.first+r.first,l.second+r.second};}

typedef long long int ll;
#define int ll
#define endl '\n'
const ll mod =1e9+7;
const ll MAX_NODES =200001;
const ll MAX_LOG =50;
const ll inf = 1e18+123;
const int maxn = 2000001;
const int N = 3005;
ll dp[N][N];
vector<pair<int,ll>> g[N];
void dfs(int u,int len,ll d){

  dp[u][len] = min(dp[u][len],d);
  for(auto v:g[u])
    dfs(v.first,len+1,v.second + d);
}

bool Q;
struct Line {
	mutable ll k, m, p;//slope, y-intercept, last optimal x
	bool operator<(const Line& o) const {
		return Q ? p < o.p : k < o.k;
	}
};
struct LineContainer : multiset<Line> {
	const bool minmax;
	LineContainer(bool minmax=1):minmax(minmax) {
	}
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
	    if (b < 0) a *= -1, b *= -1;
	    if (a >= 0) return a/b;
	    return -((-a+b-1)/b);
	}

	// updates x->p, determines if y is unneeded
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return 0; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}

	void add(ll k, ll m) {
		if(minmax)
			k*=-1,m*=-1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}

	ll query(ll x) {
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return (minmax?-1:1)*(l.k * x + l.m);
	}
};
LineContainer loc[N];

int32_t main()
{
  #ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif
   IOS
  int n,m;
  cin>>n>>m;
  for(int i = 1;i<=m;i++){
    ll u,v,w;
    cin>>u>>v>>w;
    g[u].push_back({v,w});
  }
  for(int i =  1;i<=n;i++)
    for(int j = 0;j<=n;j++)
      dp[i][j] = inf;

  dfs(1,0,0);
  for(int i = 1;i<=n;i++)
  {
    for(int j = 0;j<=n;j++){
      if(dp[i][j] != inf)
        loc[i].add(j,dp[i][j]);
    }
  }
  int q;
  cin>>q;
  ll curr = 0;
  while(q--){
    ll type,val;
    cin>>type>>val;
    if(type == 1)
      curr += val;
    else{
      if(loc[val].size())
        cout<<loc[val].query(curr)<<endl;
      else cout<<"No Path Exists"<<endl;
    }
  }
} 
