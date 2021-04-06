#include <bits/stdc++.h>
 
#define ll long long
#define X first
#define Y second
#define MP make_pair
 
using namespace std;
 
const int N = 1e5 + 12, mod = 1e9 + 7, bs = 500;
const ll INF = 1e18;

ll bin_pow(ll x, ll y){
	ll res = 1ll;
	while(y){
		if(y & 1ll)
			res = res * x % mod;
		x = x * x % mod;
		y >>= 1ll;
	}
	return res;
}

ll fact[N], rfact[N];

ll CnK(ll x, ll y){
	if(x < y)
		return 0LL;
	return (fact[x] * rfact[y] % mod * rfact[x - y] % mod);
}

int n, m, p;
bool was[N];
ll dp[15][15][(1 << 14)], ans;
map< pair<int, int>, bool > mp;
vector< int > g;

void solve(){
	mp.clear(), g.clear();
	memset(was, 0, sizeof(was));
	memset(dp, 0, sizeof(dp));
	p = ans = 0;

	cin >> n >> m;
	for(int i = 1, x ,y;i <= m;i++){
		cin >> x >> y;
		if(!was[x])
			was[x] = 1, g.push_back(x), p += 1;
		if(!was[y])
			was[y] = 1, g.push_back(y), p += 1;
		mp[MP(x, y)] = mp[MP(y, x)] = 1;
	}	
	if(p == 0)
		return void(cout << fact[n] << "\n");
	for(int i = 0;i < p;i++)
		dp[0][i][(1 << i)] = 1;
	for(int mask = 1;mask < (1 << p);mask++){
		for(int bad = 0;bad < p;bad++){
			for(int j1 = 0;j1 < p;j1++){
				if((mask >> j1) & 1)
					continue;
				int newmask = mask ^ (1 << j1);
				for(int j2 = 0;j2 < p;j2++){
					if((mask >> j2) & 1)
						dp[bad + mp.count(MP(g[j1], g[j2]))][j1][newmask] = (dp[bad + mp.count(MP(g[j1], g[j2]))][j1][newmask] + dp[bad][j2][mask]) % mod;
					else
						continue;
				}
			}
			if(mask == (1 << p) - 1){
				for(int j1 = 0;j1 < p;j1++){
					ll cf = CnK(n - bad, p) * fact[n - p] % mod;
					ans = (ans + dp[bad][j1][mask] * cf % mod) % mod;
				}	
			}
		}	
	}
	cout << ans << "\n";
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	fact[0] = 1;
	for(int i = 1;i < N;i++)
		fact[i] = fact[i - 1] * i % mod;
	rfact[N - 1] = bin_pow(fact[N - 1], mod - 2);
	for(int i = N - 2;i >= 0;i--)
		rfact[i] = rfact[i + 1] * (i + 1) % mod;

	int T;
	cin >> T;
	while(T--)
		solve();
}
