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
 
using namespace std;	

const int N = 1e5 + 10;
const int L = sqrt(2 * N);
const int P = 500;

int n, q, a[N], id[N], cnt[N / P + 1][N], freq[N / P + 1][N / P + 1][L + 2];
vector <int> v, g[N / P + 1];

int occurs(int l, int r, int x) {
	if (l > r) return 0;
	return cnt[r][x] - (l > 0 ? cnt[l - 1][x] : 0);
}

int F[L + 2], C[N], last[N], fq;

int main() {	
	scanf ("%d%d", &n, &q);
	rep(i, 0, n - 1) {
		scanf ("%d", a + i);
		v.pb(a[i]);
		id[i] = i / P;
	}
	sort(all(v));
	v.erase(unique(all(v)), v.end());
	int k = (n + P - 1) / P;
	int vals = ss(v) - 1;
	rep(i, 0, n - 1) {
		a[i] = (int) (lower_bound(all(v), a[i]) - v.begin());
		g[id[i]].pb(a[i]);
	}
	rep(i, 0, k - 1) {
		sort(all(g[i]));
		g[i].erase(unique(all(g[i])), g[i].end());
	}
	rep(i, 0, n - 1)
		cnt[id[i]][a[i]]++;
	rep(i, 1, k - 1)
		rep(j, 0, vals)
			cnt[i][j] += cnt[i - 1][j];
	rep(i, 0, k - 1)
		rep(j, 0, vals)
			if (occurs(i, i, j) <= L)
				freq[i][i][occurs(i, i, j)]++;
	rep(len, 2, k) {
		rep(l, 0, k - 1) {
			int r = l + len - 1;
			if (r >= k) continue;
			rep(j, 0, L)
				freq[l][r][j] = freq[l + 1][r][j];
			for (auto it : g[l]) {
				int old = occurs(l + 1, r, it);
				int now = occurs(l, r, it);
				if (old <= L)
					freq[l][r][old]--;
				if (now <= L)
					freq[l][r][now]++;
			}
		}
	}
	int ans = 0;
	while (q--) {
		int l, r;
		scanf ("%d%d", &l, &r);
		l ^= ans, r ^= ans;
		l--; r--;
		int LID = id[l], RID = id[r];
		rep(i, 0, L) F[i] = (LID < RID ? freq[LID + 1][RID - 1][i] : 0);
		fq++;
		auto add = [&](int x) {
			if (last[x] != fq) {
				last[x] = fq;
				int old = occurs(LID + 1, RID - 1, x);
				if (old <= L) F[old]--;
				if (old + 1 <= L) F[old + 1]++;
				C[x] = old + 1;
			}
			else {
				if (C[x] <= L) F[C[x]]--;
				C[x]++;
				if (C[x] <= L) F[C[x]]++;
			}
		};
		while (l <= r && id[l] == LID) 
			add(a[l++]);
		while (l <= r && id[r] == RID)
			add(a[r--]);
		ans = 1;
		while (F[ans]) ans++;
		printf ("%d\n", ans);
	}
				
	
	
	return 0;
}	
