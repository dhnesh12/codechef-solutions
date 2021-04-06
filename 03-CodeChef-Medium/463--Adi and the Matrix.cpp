#include<bits/stdc++.h>
#define mod 1000000007
#define maxn 1005
#define endl '\n'
using namespace std;
typedef long long ll;
ll fac[maxn], ifac[maxn], inv[maxn];
ll gc[maxn][maxn];
ll n, m;
ll qpow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b&1) res =res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
ll INV(ll x) {
	return qpow(x, mod-2);
}
ll ans = 0;
void init() {
	fac[0]=1;
	ifac[0]=1;
	fac[1]=1;
	ifac[1]=1;
	for(int i=2; i<=maxn-1; i++)
		fac[i]=fac[i-1]*i%mod,ifac[i]=mod-(mod/i)*ifac[mod%i]%mod;
	for(int i=1; i<=maxn-1; i++)
		ifac[i]=ifac[i-1]*ifac[i]%mod;
	inv[0] = 1;
	for(int i=1; i<=maxn; i++) inv[i] = fac[i-1]*ifac[i]%mod;
	for(int i=1; i<=maxn-1; i++) {
		for(int j=1; j<=maxn-1; j++) {
			gc[i][j] = gc[j][i] = __gcd(i, j);
		}
	}
}
vector<int> V;
int dp[maxn][maxn];
void cal() {
	memset(dp,0,sizeof(dp));

	ll cur = fac[n];
	int len = V.size();
	V.push_back(-1);
	for(int i=0; i<len; i++) {
		ll del = 1;
		while(i<len && V[i] == V[i+1]) del++, i++;
		cur *= INV(qpow(V[i],del))*ifac[del]%mod;
		cur %= mod;
	}
	V.pop_back();
	dp[m][m] = 1;
	for(int i=m; i>=0; i--) {
		for(int j=m; j>=1; j--) {
			if(dp[i][j]) {
				ll tmp = 0;
				for(int k=0; k<V.size(); k++) {
					tmp += gc[V[k]][j];
					tmp %= mod;
				}
				//	cout << tmp << endl;
				ll tmpp = dp[i][j];
				for(int k=0; j*k<=i; k++) {
					dp[i-j*k][j-1] += tmpp*ifac[k]%mod;
					dp[i-j*k][j-1] %= mod;
					tmpp *= inv[j]*(qpow(2,tmp))%mod;
					tmpp %= mod;
					//	cout << tmpp << endl;
				}
			}
		}
	}
//	cout << cur << " " << dp[0][0]*fac[m]%mod << endl;
	ans += dp[0][0]*fac[m]%mod*cur%mod;
	ans %= mod;
//	cout << ans << endl;
	return;
}
int cnt=0;
void dfs(int left, int cur) {
	if(!left) {
		//	for(int i=0; i<V.size(); i++) cout << V[i] << " ";
		//	cout << endl;
		cal();
		return;
	}
	if(cur == 0) return;
	for(int i=min(left, cur); i>=1; i--) {
		V.push_back(i);
		dfs(left-i,i);
		V.pop_back();
	}
}
int main() {

	cin >> n >> m;
	if(n>m) swap(n, m);
	init();
	dfs(n, n);
//	cout << ans << endl;
	cout << ans*ifac[n]%mod*ifac[m]%mod<< endl;
}