#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 1000000007;
const int Maxn = 105;
const int Maxm = 100005;

ll a[100010];
ll xi[100010];
ll prex[100010];

int t;
int n, m, k;
vector <int> neigh[Maxn];
int dp[Maxn][Maxm];
int spec[Maxn];
int midl, midr, cnt;

void traverseSimple(int v, int p = 0)
{
	for (int j = 1; j <= m; j++)
		dp[v][j] = 1;
	for (int i = 0; i < neigh[v].size(); i++) {
		int u = neigh[v][i];
		if (u == p) continue;
		traverseSimple(u, v);
		for (int j = 1; j <= m; j++) {
			int sum = (dp[u][m] - dp[u][0] + mod) % mod;
			int lef = max(1, j - k + 1), rig = min(m, j + k - 1);
			if (lef <= rig) {
				int sub = (dp[u][rig] - dp[u][lef - 1] + mod) % mod;
				sum = (sum - sub + mod) % mod;
			}
			dp[v][j] = ll(dp[v][j]) * sum % mod;
		}
	}
	for (int j = 1; j <= m; j++) 
		dp[v][j] = (dp[v][j] + dp[v][j - 1]) % mod;
}

int getSum(int u)
{
	int res = (dp[u][m - cnt] - dp[u][0] + mod) % mod;
	res = (res + ll(cnt) * spec[u]) % mod;
	return res;
}

int getReal(int ind) { return ind < midl? ind: ind + cnt; }

int Get(int u, int ind)
{
	int res = 0;
	if (ind >= midr) {
		res = ll(cnt) * spec[u] % mod;
		res = (res + dp[u][ind - cnt]) % mod;
		return res;
	}
	if (ind >= midl) {
		res = ll(ind - midl + 1) * spec[u] % mod;
		ind = midl - 1;
	}
	res = (res + dp[u][ind]) % mod;
	return res;
}

void traverseHard(int v, int p = 0)
{
	for (int j = 1; j + cnt <= m; j++)
		dp[v][j] = 1;
	spec[v] = 1;
	for (int i = 0; i < neigh[v].size(); i++) {
		int u = neigh[v][i];
		if (u == p) continue;
		traverseHard(u, v);
		for (int j = 1; j + cnt <= m; j++) {
			int sum = getSum(u);
			int realind = getReal(j);
			int lef = max(1, realind - k + 1), rig = min(m, realind + k - 1);
			if (lef <= rig) {
				int sub = (Get(u, rig) - Get(u, lef - 1) + mod) % mod;
				sum = (sum - sub + mod) % mod;
			}
			dp[v][j] = ll(dp[v][j]) * sum % mod;
		}
		int sum = getSum(u);
		int realind = midl;
		int lef = max(1, realind - k + 1), rig = min(m, realind + k - 1);
		if (lef <= rig) {
			int sub = (Get(u, rig) - Get(u, lef - 1) + mod) % mod;
			sum = (sum - sub + mod) % mod;
		}
		spec[v] = ll(spec[v]) * sum % mod;
	}
	for (int j = 1; j <= m - cnt; j++)
		dp[v][j] = (dp[v][j] + dp[v][j - 1]) % mod;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 1; i <= n; i++)
			neigh[i].clear();
		for (int i = 0; i < n - 1; i++) {
			int a, b; scanf("%d %d", &a, &b);
			neigh[a].push_back(b);
			neigh[b].push_back(a);
		}
		if (m > 40000) {
			cnt = m - 40000;
			midl = 20001;
			midr = m - 20000;
			traverseHard(1);
			printf("%d\n", Get(1,m));
		} else {
			traverseSimple(1);
			printf("%d\n", dp[1][m]);
		}
	}
	return 0;
}



void ini(ll x,ll n)
{
    xi[0]=1;
    for(ll i=1;i<n+3;i++)
        xi[i]=(xi[i-1]*x)%mod;
    prex[0]=xi[0];
    for(ll i=1;i<n+3;i++)
    {
        prex[i]=(xi[i]+prex[i-1])%mod;
    }
}