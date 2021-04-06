#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;
 
#define F first
#define S second
 
const int MAXN = 1e5 + 10;
const int SQ = 333; // <3
const int LOG = 9;
const int LIM = 100;

int n, q;
ll a[MAXN];

ll pre[MAXN], lz[SQ], nxt[MAXN][LOG];
int stk[SQ]; 

void rebuild(int l) {
	int r = min(l + SQ, n);
	for(int i = l; i < r; i++) {
		a[i] += lz[l/SQ];
		pre[i] = a[i];
		if(i > l)
			pre[i] = max(pre[i], pre[i-1]);
	}
	lz[l/SQ] = 0;
	int sz = 0;
	for(int i = r-1; i >= l; --i) {
		while(sz && a[stk[sz-1]] <= a[i])
			--sz;
		if(sz && stk[sz-1] - i > LIM)
			sz = 0;
		if(sz)
			nxt[i][0] = stk[sz-1];
		else
			nxt[i][0] = -1;
		stk[sz++] = i;
	}
	for(int j = 1; j < LOG; j++)
		for(int i = l; i < r; i++)
			if(~nxt[i][j-1])
				nxt[i][j] = nxt[nxt[i][j-1]][j-1];
			else
				nxt[i][j] = -1;
}

void upd(int l, int r, int xx) {
	
	int block = l/SQ;
	for(; l < r && l % SQ != 0; l++) {
		a[l] += xx;
	}
	rebuild(block*SQ);
	
	for(; l/SQ != r/SQ; l += SQ) {
		lz[l/SQ] += xx;
	}
	
	block = l/SQ;
	for(; l < r; l++) {
		a[l] += xx;
	}
	rebuild(block*SQ);
}

int jump(int i, int &k) {
	for(int j = LOG-1; ~j; --j) {
		if(k >= (1<<j)) {
			if(~nxt[i][j]) {
				i = nxt[i][j];
				k -= 1<<j;
			}
		}
	}
	return i;
}

int go(int i, int k) {
	i = jump(i, k);

	while(k) {
		ll xx = a[i] + lz[i/SQ];
		
		int l = (i/SQ+1)*SQ;
		if(l >= n) {
			break;
		}
		int r = min(l + SQ, n);
		
		int j = upper_bound(pre+l, pre+r, xx - lz[l/SQ]) - pre;
		if(j-i > LIM || j == r)
			break;
		--k;
		i = jump(j, k);
	}
	
	return i;
}

void solve() {
	cin >> n >> q;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i += SQ)
		rebuild(i);
	while(q--) {
		int ty; cin >> ty;
		if(ty == 1) {
			int i, k; cin >> i >> k; --i;
			cout << go(i, k) + 1 << "\n";
		} else {
			int l, r, x; cin >> l >> r >> x; --l;
			upd(l, r, x);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//cout << fixed << setprecision(6);
	
	int te = 1;	
	//cin >> te;
	for (int w = 1; w <= te; w++){
		//cout << "Case #" << w << ": ";
		solve();
	}
	return 0;
}
