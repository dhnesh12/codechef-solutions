# include <stdio.h>
# include <bits/stdc++.h>


#define _USE_MATH_DEFINES_
#define ll long long
#define ld long double
#define Accepted 0
#define pb push_back
#define mp make_pair
#define sz(x) (int)(x.size())
#define every(x) x.begin(),x.end()
#define F first
#define S second
#define For(i,x,y)  for (int i = x; i <= y; i ++) 
#define FOr(i,x,y)  for (int i = x; i >= y; i --)
#define SpeedForce ios_base::sync_with_stdio(0), cin.tie(0)
// ROAD to...                                                                                                                                                                                                                Red

using namespace std;

inline bool isvowel (char c) {
	c = tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'y' || c == 'o' || c == 'u') return 1;
    return 0;
}

const double eps = 0.000001;
const ld pi = acos(-1);
const int maxn = 1e7 + 9;
const int mod = 1e9 + 7;
const ll MOD = 1e18 + 9;
const ll INF = 1e18 + 123;
const int inf = 2e9 + 11;
const int mxn = 1e6 + 9;
const int N = 2e5 + 123;                                          
const int M = 19;
const int pri = 997;
const int Magic = 2101;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
 
int n, m, k;
int c[N];
int u[(1 << M)];
ll dp[(1 << M)];

int main () {
	SpeedForce;    
   int T;
   cin >> T;
   for (int timer = 1; timer <= T; timer ++) {
   	
   	cin >> n >> m; 	
   	for (int i = 0; i < n; i ++) {
   		cin >> c[i];
   	}
   	for (int mask = 1; mask < (1 << n); mask ++) {
   		dp[mask] = 0;
   		for (int j = 0; j < n; j ++) {
   			if (mask & (1 << j))
   				dp[mask] += c[j];
   		}
   	}
   	vector < pair < ll, ll > > v;
   	for (int i = 1; i <= m; i ++) {
   		ll p, q, msk = 0;
   		cin >> p >> q;
   		for (int j = 0; j < q; j ++) {
   			int x;
   			cin >> x;
   			x --;
   			msk |= (1 << x);
   		}
   		v.pb(mp(p, msk));
   	}
   	sort(every(v));
   	for (auto it : v) {
   		ll msk = it.S;
   		ll p = it.F;
   		if(dp[msk] <= p) continue;
   		for (int mask = 0; mask < (1 << n); mask ++) {
   			dp[mask | msk] = min(dp[mask | msk], dp[mask] + p);
   		}
   	}
   	cout << dp[(1 << n) - 1] << '\n';
   }
    return Accepted;
}

// Coded By OB