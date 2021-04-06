#include<bits/stdc++.h>
using namespace std;
#define LL long long 
const int MAXN = 1e6 + 10;
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}

int prime[MAXN], tot, vis[MAXN];

int tim[MAXN], a[MAXN];

void sieve(int N) {
	for(int i = 2; i <= N; i++) {
		if(!vis[i]) prime[++tot] = i;
		for(int j = 1; j <= tot && 1ll * i * prime[j] <= N; j++) {
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
}

vector<int> gar;

void fact(int x) {
	for(int i = 1; i <= tot && 1ll * prime[i] * prime[i] <= x; i++) {
		if(x % prime[i] == 0) {
			int cnt = 0;
			while(x % prime[i] == 0) cnt++, x /= prime[i];
			if(cnt & 1) tim[i]++, gar.push_back(i);
		}
	}
	if(x != 1) {
		int pos = lower_bound(prime + 1, prime + tot + 1, x) - prime;
		tim[pos]++;
		gar.push_back(pos);
	}
}


void solve() {
//	memset(tim, 0, sizeof(tim));//
	int N = read();
	for(int i = 1; i <= N; i++) {
		a[i] = read();
		fact(a[i]);
	}
	LL ans = 0;
	for(auto i: gar) {
		ans += min(tim[i], N - tim[i]), tim[i] = 0;
	}
	gar.clear();
	cout << ans << '\n';
}

signed main() {
	sieve(1e6 + 10);
//	cout << tot;
	for(int T = read(); T--; solve());
	return 0;
}
/*
3
3
2 2 2
3
1 2 2
3
2 4 6
*/
