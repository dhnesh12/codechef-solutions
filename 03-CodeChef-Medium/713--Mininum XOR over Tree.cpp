#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define ld long double
#define pii pair <int,int>
#define pll pair <ll,ll>
#define pil pair <int,ll>
#define pli pair <ll,int>
#define pss pair <short,short>
#define ull unsigned long long
#define pdd pair <ld,ld> 
#define pb push_back
#define mp make_pair
#define puu pair<ull,ull>
#define pvv pair<vector<int>, vector<int> >
#define _bp __builtin_popcount
#define ptt pair <pnode,pnode>
#define all(v) v.begin(),v.end()
#define en "\n"
void file()
{
    freopen("fcolor.in","r",stdin);
    freopen("fcolor.out","w",stdout);
}
void boos()
{
	ios_base :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
//const long double pi = acos(-1);
const ll INF = (ll)1e9 + 7ll;
const ll INF1 = 998244353;
const ll INF2 = (ll)1e9 + 9ll;
const ll LLINF = (ll)3e18;
const ll INTmx = (ll)1e9;
const ld EPS = (ld)1e-15;
const int N = 2e5 + 100;
int tin[N],tout[N],Tima,a[N];
pii b[N];
vector <int> g[N];
vector <pii> t[N * 4];
void dfs(int v,int p)
{
	tin[v] = ++Tima;
	b[Tima] = mp(a[v],v);
	for(int i = 0;i < g[v].size();i++)
	{
		int to = g[v][i];
		if(to == p)continue;
		dfs(to,v);
	}
	tout[v] = Tima;
}
void build(int v,int tl,int tr)
{
	t[v].clear();
	if(tl == tr)
	{
		t[v].pb(b[tl]);
		return;
	}
	int tm = (tl + tr) / 2;
	build(v + v,tl,tm);
	build(v + v + 1,tm + 1,tr);
	int L = 0,R = 0;
	while(L < t[v + v].size() || R < t[v + v + 1].size())
	{
		if(L == t[v + v].size())
		{
			t[v].pb(t[v + v + 1][R++]);
			continue;
		}
		if(R == t[v + v + 1].size())
		{
			t[v].pb(t[v + v][L++]);
			continue;
		}
		if(t[v + v][L] < t[v + v + 1][R])
		{
			t[v].pb(t[v + v][L++]);
		}else {
			t[v].pb(t[v + v + 1][R++]);
		}
	}
}
pii get(int v,int tl,int tr,int l,int r,int k)
{
	//cout << v << " " << tl << " " << tr << endl;
	if(tl > r || tr < l)return mp(0,-INF);
	if(tl >= l && tr <= r)
	{
		int L = 0,R = tr - tl,ans = tr - tl + 1;
		int tek = 0;
		for(int i = 19;i >= 0;i--)
		{
			if(R - L + 1 <= 100)break;
			int lx = L,rx = R;
			ans = tr - tl + 1;
			if(!(k & (1 << i)))
			{
				tek = (tek | (1 << i));
				if(t[v][R].f < tek)
				{
					tek = (tek ^ (1 << i));
					continue;
				}
				while(L <= R)
				{
					int mid = (L + R) / 2;
					if(t[v][mid].f >= tek)
					{
						ans = mid;
						R = mid - 1;
					}else {
						L = mid + 1;
					}
				}
				lx = max(lx,ans);
			}else {
				if(t[v][L].f >= (tek + (1 << i)))
				{
					tek = (tek ^ (1 << i));
					continue;
				}
				ans = 0;
				while(L <= R)
				{
					int mid = (L + R) / 2;
					if(t[v][mid].f <= (tek + (1 << i)))
					{
						ans = mid;
						L = mid + 1;
					}else {
						R = mid - 1;
					}
				}
				rx = min(rx,ans);
			}
			L = lx,R = rx;
			if(R - L + 1 <= 130)break;
		} 
		//cout << L << " " << R << " -- " << tek << endl;
		pii ans1 = mp(0,-INF);
		for(int i = L;i <= R;i++)
		{
			ans1 = max(ans1,mp((t[v][i].f ^ k),-t[v][i].s));
		}
		return ans1;
	}
	int tm = (tl + tr) / 2;
	return max(get(v + v,tl,tm,l,r,k),get(v + v + 1,tm + 1,tr,l,r,k));
}
int main()
{
	//boos();
	//file();
	int Van;
	cin >> Van;
	while(Van--)
	{
		int n,q;
		cin >> n >> q;
		for(int i = 1;i <= n;i++)
		{
			cin >> a[i];
			g[i].clear();
		}
		Tima = 0;
		for(int i = 1;i < n;i++)
		{
			int x,y;
			cin >> x >> y;
			g[x].pb(y);
			g[y].pb(x);
		}
		dfs(1,-1);
		build(1,1,n);
		int lastv = 0,lastk = 0;
		for(int i = 1;i <= q;i++)
		{
			int v,k;
			cin >> v >> k;
			v = (v ^ lastv);
			k = (k ^ lastk);
			int tek = 0;
			pii ans = get(1,1,n,tin[v],tout[v],k);
			ans.s = -ans.s;
			cout << ans.s << " " << ans.f<< en;
			lastv = ans.s;
			lastk = ans.f;
		}
	}
}