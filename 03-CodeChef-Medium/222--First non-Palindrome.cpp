#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ss(x) (int) x.size()
#define fi first
#define se second
#define cat(x) cerr << #x << " = " << x << endl
#define rep(i, j, n) for (int i = j; i <= n; ++i)
#define per(i, j, n) for (int i = n; j <= i; --i)
#define all(x) x.begin(), x.end()
#define ull unsigned long long
 
using namespace std;		

const int N = 1e5 + 101;
const int base = 31;
const int mod = 1e9 + 7;

char s[N];

int n;
int first[26][2];
int k[N];

int h[N][2];
int pot[N];

int Left(int l, int r) {
	return (h[r][0] - 1LL * h[l - 1][0] * pot[r - l + 1] % mod + mod) % mod;
}

int Right(int l, int r) {
	return (h[l][1] - 1LL * h[r + 1][1] * pot[r - l + 1] % mod + mod) % mod;
}

bool ispal(int l, int r) {
	return Left(l , r) == Right(l, r);
}

void solve() {
	scanf ("%s", s + 1);
	int n = strlen(s + 1);
	
	pot[0] = 1;
	rep(i, 1, n)
		pot[i] = 1LL * pot[i - 1] * base % mod;
		
	rep(i, 1, n)
		h[i][0] = (1LL * h[i - 1][0] * base + s[i]) % mod;
	h[n + 1][1] = 0;
	per(i, 1, n)
		h[i][1] = (1LL * h[i + 1][1] * base + s[i]) % mod;
	
	rep(c, 0, 25)
		rep(i, 0, 1)
			first[c][i] = n + 1;
	rep(i, 1, n) {
		int c = s[i] - 'a';
		first[c][i % 2] = min(first[c][i % 2], i);
	}
	k[1] = 0;
	rep(i, 2, n) {
		k[i] = 0;
		if (!ispal(1, i)) {
			k[i] = 1;
			continue;
		}
		if (i == n) continue;
		if (!ispal(2, i + 1)) {
			k[i] = 2;
			continue;
		}
		int c1 = s[1] - 'a';
		int c2 = s[2] - 'a';
		int m1 = n + 1;
		int m2 = n + 1;
		rep(j, 0, 25) {
			if (c1 != j)
				m1 = min(m1, first[j][1]);
			if (c2 != j)
				m2 = min(m2, first[j][0]);
		}
		m1 = min(m1, m2);
		if (m1 == n + 1) k[i] = 0;
		else k[i] = m1 - i + 1;
	}
	
	ull answer = 0;
	ull p = 1;
	per(i, 1, n) {
		//cat(k[i]);
		answer += p * k[i];
		p *= 100007;
	} 
	printf ("%llu\n", answer);
}

int main() {	
	int T;
	scanf ("%d", &T);
	while (T--) solve();
	
	return 0;
}	
