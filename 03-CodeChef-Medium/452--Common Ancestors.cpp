#pragma GCC optimize ("Ofast")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize ("-ffloat-store")

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pop_b pop_back
#define pf push_front
#define pop_f pop_front
#define mt make_tuple
#define eb emplace_back

typedef int64_t ll;
#define int int64_t
#define LB(x,v) (ll)(lower_bound(x.begin(),x.end(),v)-x.begin())
#define UB(x,v) (ll)(upper_bound(x.begin(),x.end(),v)-x.begin())
#define len(x) (ll)x.length()
#define sz(x) (ll)x.size()
typedef pair<ll,ll> ii;
typedef long double ld; 
typedef vector<int> vi;
typedef vector<set<ll>> vset;

typedef vector<ll> vl;
typedef vector<ld> vd;
typedef unsigned long long ull;

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; }; sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0); sim > char dud(...);
struct debug {
#ifdef LOCAL
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i));}
sim, class b dor(pair < b, c > d) {ris << "(" << d.first << ", " << d.second << ")";}
sim dor(rge<c> d) {*this << "["; for (auto it = d.b; it != d.e; ++it) *this << ", " + 2 * (it == d.b) << *it; ris << "]";}
#else
sim dor(const c&) { ris; }
#endif
};
vector<char*> tokenizer(const char* args) {
    char *token = new char[111]; strcpy(token, args); token = strtok(token, ", ");
    vector<char*> v({token});
    while(token = strtok(NULL,", ")) v.push_back(token);
    return reverse(v.begin(), v.end()), v;
}
void debugg(vector<char*> args) { cerr << "\b\b "; }
template <typename Head, typename... Tail>
void debugg(vector<char*> args, Head H, Tail... T) {
    debug() << " [" << args.back() << ": " << H << "] ";
    args.pop_back(); debugg(args, T...);
}
#define harg(...) #__VA_ARGS__
#ifdef LOCAL
#define dbg(...) { debugg(tokenizer(harg(__VA_ARGS__, \b\t-->Line)), __VA_ARGS__, __LINE__); cerr << endl;}
#else
#define dbg(...) { }
#endif

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define Rep(i, n) for (ll i = 1; i <= (n); i++)
#define repr(i, n) for (ll i = (n) - 1; i >= 0; i--)
#define rep2(i, l, r) for (ll i = (l); i < (r); i++)
#define rep2r(i, l, r) for (ll i = (r) - 1; i >= (l); i--)
#define all(a) a.begin(), a.end()
#define cinai(a, n) vi a(n); rep(fukre, n) { cin>>a[fukre]; }
#define cinal(a, n) vl a(n); rep(fukre, n) { cin>>a[fukre]; }
#define coutai(a, n) rep(fukre, n) { cout<<a[fukre]<<" "; } ent;
#define coutal(a, n) rep(fukre, n) { cout<<a[fukre]<<" "; } ent;
#define resize_vec(a) a.resize(unique(a.begin(), a.end()) - a.begin());
#define ms(dp, x) memset(dp, x, sizeof(dp))
#define endl '\n'
#define ent cout<<endl;

ll powm(ll a, ll b, ll mod) {
	ll res=1;
	while(b) {
		if(b&1)
			res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
const ld pi = 3.14159265358979323846;
const ll mod = 1e9 + 7;
const ll N = 1000005;
const ll inf = 1e9;
const ll INF = 1e18;

#define ii pair<int, int>
struct SegTree
{
    int N;
    vector<int> lazy;
    vector<bool> cLazy;
    vector<pair<int, int>> seg;
 
    void init(int n)
    {
        N = n;
        seg.resize(4 * N + 5, make_pair(0, 0));
        cLazy.assign(4 * N + 5, false);
        lazy.resize(4 * N + 5, 0);
    }

    void update(int node,int start,int end,int l,int r,int val){
        if(lazy[node]!=0){
            seg[node].fi+=lazy[node];
            seg[node].se+=lazy[node];
            if(start!=end){
                lazy[node<<1]+=lazy[node];
                lazy[node<<1|1]+=lazy[node];
            }
            lazy[node]=0;
        }
        if(start>end || start>r || end<l) return;
        if(l<=start && end<=r){
            seg[node].fi+=val;
            seg[node].se+=val;
            if(start!=end){
                lazy[node<<1]+=val;
                lazy[node<<1|1]+=val;
            }
            return;
        }
        int mid=(start+end)>>1;
        update(node<<1,start,mid,l,r,val);
        update(node<<1|1,mid+1,end,l,r,val);
        seg[node].fi=max(seg[node<<1].fi,seg[node<<1|1].fi);
        seg[node].se=min(seg[node<<1].se,seg[node<<1|1].se);
    }
    ii query(int node,int start,int end,int l,int r){
        if(start>end || start>r || end<l) return {-inf,inf};
        if(lazy[node]!=0){
            seg[node].fi+=lazy[node];
            seg[node].se+=lazy[node];
            if(start!=end){
                lazy[node<<1]+=lazy[node];
                lazy[node<<1|1]+=lazy[node];
            }
            lazy[node]=0;
        }
        if(start>=l && end<=r) return seg[node];
        int mid=(start+end)>>1;
        ii q1=query(node<<1,start,mid,l,r);
        ii q2=query(node<<1|1,mid+1,end,l,r);
        return {max(q1.fi,q2.fi),min(q1.se,q2.se)};
    }
    ii query(int pos)
    {
        return query(1, 1, N, pos, pos);
    }
 
    ii query(int l, int r)
    {
        return query(1, 1, N, l, r);
    }
 
    void update(int pos, int val)
    {
        update(1, 1, N, pos, pos, val);
    }
 
    void update(int l, int r, int val)
    {
        update(1, 1, N, l, r, val);
    }
};


void solve()
{
	int n;
	cin>>n;
	vector<vector<vi>> adj(2, vector<vi>(n));
	int rt[2];
	rep(j, 2){
		rep(i, n){
			int x;
			cin>>x;
			if(x == -1)
				rt[j] = i;
			else{
				x--;
				adj[j][x].pb(i);
			}
		}
	}
	SegTree seg;
	seg.init(2 * n);
	vi st(n), ed(n);
	int tim = 0;
	function<void(int)> dfs0 = [&](int src) {
		st[src] = tim++;
		for(int i : adj[0][src])
			dfs0(i);
		ed[src] = tim++;
	};
	dfs0(rt[0]);
	// int dis[2][n];
	vector<vi> dis(2, vi(n));
	for(int i = 0; i < 2; i++){
		deque<pair<int, int>> dq;
		dq.pb(make_pair(rt[i], 0));
		while(sz(dq)){
			int u = dq.front().fi;
			int wt = dq.front().se;
			dq.pop_front();
			dis[i][u] = wt;
			for(int v : adj[i][u])
				dq.pb(make_pair(v, wt + 1));
		}
	}
	int ans = 0;
	function<void(int)> dfs1 = [&](int src) {
		if(dis[0][src] == dis[1][src]){
			seg.update(st[src], ed[src], 1);
		}
		ans = max(ans, seg.query(1, 2*n).fi);
		for(int v : adj[1][src]){
			dfs1(v);
		}

		if(dis[0][src] == dis[1][src]){
			seg.update(st[src], ed[src], -1);
		}	
	};
	dfs1(rt[1]);
	cout<<ans<<endl;
}

#define testCases
int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15);
	
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	int tc = 1;
#ifdef testCases
	cin>>tc;
#endif
	for(int t = 1; t <= tc; t++)
	{
#ifdef LOCAL
	int tt = clock();
#endif
		// cout<<"Case #"<<t<<": ";
		solve();
		
#ifdef LOCAL
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
#endif
	}
	return 0;
}


// watch 
