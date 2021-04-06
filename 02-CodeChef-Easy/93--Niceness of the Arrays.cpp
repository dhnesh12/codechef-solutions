#include <bits/stdc++.h>

#define ll long long
#define X first
#define Y second
#define MP make_pair

using namespace std;

const int N = 5e5 + 1, bs = 300;
const ll mod = 1e9 + 7, INF = 1e18;

ll fact[N], rfact[N];
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
ll ans;
int n, s, a[N], cnt;

ll CnK(ll x, ll y){
	if(y < 0)
		return 0;
	return fact[x] * rfact[y] % mod * rfact[x - y] % mod;
}

int calc(){
	int tmp = 0;
	for(int i = 1;i <= n;i++)
		for(int j = i + 1;j <= n;j++)
			tmp += __gcd(a[i], a[j]);
	return tmp;
}

inline void rec(int pos, int last, int g = 0){
	if(s < 0)
		return;
	if(pos == n + 1){
		if(s == 0)                     
			ans += calc();
		return;
	}
	if(a[pos] == -1){
		for(int i = 1;i <= s;i++)
			s -= i, a[pos] = i, rec(pos + 1, i, g + (i != last)), a[pos] = -1, s += i;
	}
	else{
		rec(pos + 1, last, g);
	}
}

void solve(){
	cnt = 0;
	ans = 0;
	scanf("%d %d", &n, &s);
	for(int i = 1;i <= n;i++)
		scanf("%d", a + i), s -= (a[i] == -1? 0: a[i]), cnt += (a[i] == -1);
	rec(1, 1);
	printf("%lld\n", ans);
}

int main () {
    fact[0] = 1;
	for(int i = 1;i < N;i++)
		fact[i] = fact[i - 1] * i % mod;
	rfact[N - 1] = bin_pow(fact[N - 1], mod - 2);
	for(int i = N - 2;i >= 0;i--)
		rfact[i] = rfact[i + 1] * (i + 1) % mod;
	int T;
	scanf("%d", &T);
	while(T--)
		solve();
}
