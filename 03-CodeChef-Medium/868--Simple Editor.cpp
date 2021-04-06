/**
 *	author:   fractal
 *	co-author: 288481RF
 *	created: 02/17/21 00:32:35
**/

#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second 
#define mp make_pair
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define speed ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define sz(x) (int)x.size()
#define len(x) (int)strlen(x)
#define all(x) x.begin(), x.end()
#define debug cerr << "OK\n";
#define ub upper_bound
#define lb lower_bound 
#define clbuff fflush(stdin);
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef set <int> si;
typedef set <ll> sll;
typedef multiset <int> msi;
typedef multiset <ll> msll;
typedef map <int, int> mi;
typedef map <ll, int> mll;
 
const int N = 1e5 + 2;
const int M = 1e5;
const int mod = 1e9 + 7;
const int inf = 2e9 + 3;
const ll INF = 1e18;
const ld pi2 = 2.0 * 3.141592;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

void files() {
	#ifndef PC
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
}

int n, m, sz[N], zs[N], block = 300, cnt;
int b[1000][1000], d[1000][1000];

void add(int pos, int c) {
	for (int i = 1; i <= cnt; ++i) {
		if (pos <= sz[i]) {
			++sz[i];
			for (int j = sz[i]; j >= pos + 2; --j) {
				b[i][j] = b[i][j - 1];
			}
			b[i][pos + 1] = c;
			if (sz[i] == 2 * block) {
				goto recalc;
			}
			return;
		}
		else {
			pos -= sz[i];
		}
	}
recalc:
	int nct = 1;
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; j <= sz[i]; ++j) {
			d[nct][++zs[nct]] = b[i][j];
			if (zs[nct] == block)
				nct++;			
		}
	}
	if (zs[nct] == 0)
		nct--;
	cnt = nct;
	for (int i = 1; i <= cnt; ++i) {
		sz[i] = zs[i];
		zs[i] = 0;
		for (int j = 1; j <= sz[i]; ++j)
			b[i][j] = d[i][j];
	}
}

void get(int pos, int len) {
	for (int i = 1; i <= cnt; ++i) {
		if (pos <= sz[i]) {
			for (int j = pos; j <= sz[i]; ++j) {
				cout << char(b[i][j] + 'a');
				--len;
				if (len == 0) {
					cout << '\n';
					return;
				}
			}
			pos = 1;
		}
		else {
			pos -= sz[i];
		}
	}
}

int main() {
	speed;
	cin >> m;
	cnt = 1;
	sz[1] = 1;
	b[1][1] = 0;	
	while (m--) {
		int l, r;
		string s;
		char C;
		cin >> C >> l;
		++l;
		if (C == '+') {
			cin >> s;
			for (auto it : s)
				add(l++, it - 'a');
		}
		else {
			cin >> r;
			get(l, r);
		}		
	}
}
