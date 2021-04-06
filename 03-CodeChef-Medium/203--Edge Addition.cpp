//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long

#define mp make_pair
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define ii pair<int, int>
#define vi vector<int>
#define vii vector<ii>

typedef long double ld;

const int mod = 1e9+7;
const ld pi = 4*atan((ld)1);

/*
cach code:
1. Nhap khung ra, xet het cac truog hop cho ro rang
2. Comment vao bai
3. Code tung phan, check can than.
4. Kiem tra lai constraint.
*/

int n, dp[205][205][205], tdp[205][205][205], A[205], B[205], C[205][205], fac[205], sz[205], pw[100005];
vi G[205];

int bp (int x, int y)
{
	int re = 1;
	while(y)
	{
		if(y & 1) re = re * x % mod;
		y >>= 1;
		x = x * x % mod; 
	}
	return re;
}
void dfs(int u, int p)
{
	sz[u] = 1;
	dp[u][0][1] = 1;
	for(auto v: G[u])
	{
		if(v != p)
		{
			dfs(v, u);
			for(int e = 0; e <= sz[u] - 1; e++) for(int now = 1; now <= sz[u]; now++) tdp[u][e][now] = 0;
			for(int _e = 0; _e <= sz[v] - 1; _e++)
			{
				for(int _now = 1; _now <= sz[v]; _now++)
				{
					for(int e = sz[u] - 1; e >= 0; e--)
					{
						for(int now = sz[u]; now >= 1; now--)
						{
							// (u, v) is bridge
							tdp[u][e + _e + 1][now] += dp[u][e][now] * dp[v][_e][_now] % mod * pw[(_now - 1) * (_now - 2) / 2] % mod;
							tdp[u][e + _e + 1][now] %= mod;
							// not bridge
							tdp[u][e + _e][now + _now] += dp[u][e][now] * dp[v][_e][_now] % mod;
							tdp[u][e + _e][now + _now] %= mod;
						}
					}
				}
			}
			sz[u] += sz[v];
			for(int e = 0; e <= sz[u] - 1; e++) for(int now = 1; now <= sz[u]; now++) dp[u][e][now] = tdp[u][e][now];
		}
	}
}
signed main()
{
//	freopen(".inp", "r", stdin);
//	freopen(".out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i <= n; i++)	fac[i] = !i? 1: fac[i - 1] * i % mod;
	for(int i = 0; i < 100005; i++) pw[i] = !i? 1: pw[i - 1] * 2 % mod;
	for(int i = 0; i <= n; i++) for(int j = i; j <= n; j++) C[i][j] = fac[j] * bp(fac[i], mod - 2) % mod * bp(fac[j - i], mod - 2) % mod;
	for(int i = 1; i <= n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
		G[v].eb(u);
	}
	dfs(1, 0);
	for(int e = 0; e <= n - 1; e++)
	{
		for(int now = 1; now <= n; now++)
		{
			B[e] = (B[e] + dp[1][e][now] * pw[(now - 1) * (now - 2) / 2] % mod) % mod;
		}
	}
	for(int e = n - 1; e >= 0; e--)
	{
		A[e] = B[e];
		for(int _e = e + 1; _e <= n - 1; _e++)
		{
			A[e] = (A[e] - C[e][_e] * A[_e] % mod + mod) % mod;
		}
	}
	for(int i = 0; i <= n - 1; i++) cout << A[i] << " ";
}




