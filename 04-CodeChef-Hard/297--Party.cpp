#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;
 
#define F first
#define S second
 
const int MOD = 1e9 + 7;//XXX
const int C = 26;//XXX
 
void add(int &x, int y){
	x += y;
	while (x >= MOD) x -= MOD;
	while (x < 0) x += MOD;
}
 
int fix(int x){
	while (x >= MOD) x -= MOD;
	while (x < 0) x += MOD;
	return x;
}
 
int pw(int a, int b){
	int ret = 1;
	while (b){
		if (b & 1)
			ret = 1ll*ret*a%MOD;
		b >>= 1;
		a = 1ll*a*a%MOD;
	}
	return ret;
}
 
const int MAXN = 2e5 + 10;
const int SQ = 400;

int n, m, q, eu[MAXN], ev[MAXN], st[MAXN<<1], ans[MAXN], mark[MAXN];
vector<pii> vec[MAXN], sec[MAXN];
vector<int> upd[MAXN];

void plant(int i, int x) {
	st[i += n] = x;
	for(i >>= 1; i; i >>= 1)
		st[i] = max(st[i<<1], st[i<<1^1]);
}

int get(int a, int b) {
	int r = -1;
	for(a += n, b += n; a <= b; a >>= 1, b >>= 1) {
		if(a&1) r = max(r, st[a++]);
		if(!(b&1)) r = max(r, st[b--]);
	}
	return r;
}

void solve() {
	cin >> n >> m;
	memset(st, -1, 4*(2*n+5));
	memset(mark, -1, 4*n);
	for(int i = 0; i < n; i++) {
		upd[i].clear();
		sec[i].clear();
	}
	for(int i = 0; i < m; i++) {
		cin >> eu[i] >> ev[i];
		--eu[i], --ev[i];
		if(eu[i] > ev[i])
			swap(eu[i], ev[i]);
		upd[ev[i]].push_back(eu[i]);
	}
	cin >> q;
	for(int i = 0; i < q; i++) {
		ans[i] = 1;
		int k;
		cin >> k;
		
		if(k >= SQ) {
			for(int rep = 0, l, r; rep < k; rep++) {
				cin >> l >> r;
				--l;
				for(int j = l; j < r; j++)
					mark[j] = i;
			}
			for(int j = 0; j < m; j++)
				if(mark[eu[j]] == i && mark[ev[j]] == i) {
					ans[i] = 0;
					break;
				}
		}
		else {
			vec[i].resize(k);
			for(int j = 0; j < k; j++) {
				cin >> vec[i][j].F >> vec[i][j].S;
				--vec[i][j].F, --vec[i][j].S;
			}
			sort(vec[i].begin(), vec[i].end());
			for(int j = 0; j < k; j++) 
				sec[vec[i][j].S].emplace_back(i, j); // (qry idx, interval num)
		}
	}
	
	for(int u = 0; u < n; u++) {
		for(int v : upd[u])
			plant(v, u);
			
		for(auto& p : sec[u]) 
			for(int i = 0; i <= p.S && ans[p.F]; i++)
				if(get(vec[p.F][i].F, vec[p.F][i].S) >= vec[p.F][p.S].F)
					ans[p.F] = 0;
	}
	
	for(int i = 0; i < q; i++)
		if(ans[i])
			cout << "YES\n";
		else
			cout << "NO\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//cout << fixed << setprecision(6);
	
	int te = 1;	
	cin >> te;
	for (int w = 1; w <= te; w++){
		//cout << "Case #" << w << ": ";
		solve();
	}
	return 0;
}
