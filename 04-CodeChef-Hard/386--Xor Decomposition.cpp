/*
  _    _ _      _ _      _ _      
 | |__| | | _ _| | | _ _| | | ___
 | '_ \_  _| ' \_  _| ' \_  _(_-< 
 |_.__/ |_||_||_||_||_||_||_|/__/

*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define db(x) cout << #x << "=" << x << '\n'
#define rep(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(x) scanf("%s", x)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(x) printf("%s\n", x)
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define F first
#define S second
#define pb push_back
#define ll long long

#define X real()
#define Y imag()
#define angle(a)                (atan2((a).imag(), (a).real()))
#define vec(a,b)                ((b)-(a))
#define same(p1,p2)             (dp(vec(p1,p2),vec(p1,p2)) < EPS)
#define dp(a,b)                 ( (conj(a)*(b)).real() )	// a*b cos(T), if zero -> prep
#define cp(a,b)                 ( (conj(a)*(b)).imag() )	// a*b sin(T), if zero -> parllel
#define length(a)               (hypot((a).imag(), (a).real()))
#define normalize(a)            (a)/length(a)
//#define polar(r,ang)            ((r)*exp(point(0,ang)))  ==> Already added in c++11
#define rotateO(p,ang)          ((p)*exp(point(0,ang)))
#define rotateA(p,ang,about)  (rotateO(vec(about,p),ang)+about)
#define reflectO(v,m)  (conj((v)/(m))*(m))


typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef complex<double> point;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const double PI  = acos(-1.0);
const double EPS = 1e-9;
const int mod = 1000000007;
const int N = 1e5 + 7, M = N, OO = 1e9 + 7;
const ll LLOO = 1e18 + 7;

//=======================

vi g[N];
int a[N],n,dpe[N],dpo[N],x;
ll sum[N];

int add(int x,int y)
{
	int ret = ((ll)x+y)%mod;
	return ret;
}

int mult(int x,int y)
{
	int ret = ((ll)x*y)%mod;
	return ret;
}

ll dfs(int u,int p = -1)
{
	dpe[u] = 1;
	dpo[u] = 0;
	sum[u] = a[u];
	for(auto v:g[u])
	{
		if (v == p) continue;
		sum[u] ^= dfs(v,u);
		int dpee = dpe[u];
		int dpoo = dpo[u];
		
		dpe[u] = add(
					mult(dpee,dpe[v]),
					mult(dpoo,dpo[v]));
		if (sum[v] == x) dpe[u] = add(dpe[u],mult(dpoo,dpe[v]));
		if (sum[v] == 0) dpe[u] = add(dpe[u],mult(dpee,dpo[v]));
		
		dpo[u] = add(
					mult(dpee,dpo[v]),
					mult(dpoo,dpe[v]));
		if (sum[v] == x) dpo[u] = add(dpo[u],mult(dpee,dpe[v]));
		if (sum[v] == 0) dpo[u] = add(dpo[u],mult(dpoo,dpo[v]));
	}
	return sum[u];
}

void solve()
{
    si(n);si(x);
    rep(i,1,n+1) si(a[i]);
    
    rep(i,0,n-1)
    {
		int u,v;
		si(u);
		si(v);
		g[u].pb(v);
		g[v].pb(u);
	}
	
	ll sum = dfs(1);
	
	if (x == 0 && sum == 0) pi(add(dpo[1],dpe[1]));
	else if (sum == 0) pi(dpo[1]);
	else if (sum == x) pi(dpe[1]);
	else puts("0");
}

int main()
{
    // uncomment if file :
    // freopen("in","r",stdin);
    // freopen("out","w",stdout);
    int t = 1;
    // si(t); // uncomment if testcases
    while (t--)
        solve();
    return 0;
}


// btw i use arch
