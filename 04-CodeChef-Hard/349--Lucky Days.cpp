#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, n) for (int i = 0; i < (int)(n); ++ i)

const int blk = 107;

int a, b;
int x, y, z;
int p, c, q;

struct Mat {
	int n, m;
	int a[3][3];

	Mat() {}
	Mat(int n, int m): n(n), m(m) { memset(a, 0, sizeof(a)); }

	Mat operator * (const Mat &oth) const {
		Mat ans;
		if (oth.m == 3) {
			ans = Mat(3, 3);
			ans.a[0][0] = (a[0][0] * oth.a[0][0] + a[0][1] * oth.a[1][0] + a[0][2] * oth.a[2][0]) % p;
			ans.a[0][1] = (a[0][0] * oth.a[0][1] + a[0][1] * oth.a[1][1] + a[0][2] * oth.a[2][1]) % p;
			ans.a[0][2] = (a[0][0] * oth.a[0][2] + a[0][1] * oth.a[1][2] + a[0][2] * oth.a[2][2]) % p;
			ans.a[1][0] = (a[1][0] * oth.a[0][0] + a[1][1] * oth.a[1][0] + a[1][2] * oth.a[2][0]) % p;
			ans.a[1][1] = (a[1][0] * oth.a[0][1] + a[1][1] * oth.a[1][1] + a[1][2] * oth.a[2][1]) % p;
			ans.a[1][2] = (a[1][0] * oth.a[0][2] + a[1][1] * oth.a[1][2] + a[1][2] * oth.a[2][2]) % p;
			ans.a[2][0] = (a[2][0] * oth.a[0][0] + a[2][1] * oth.a[1][0] + a[2][2] * oth.a[2][0]) % p;
			ans.a[2][1] = (a[2][0] * oth.a[0][1] + a[2][1] * oth.a[1][1] + a[2][2] * oth.a[2][1]) % p;
			ans.a[2][2] = (a[2][0] * oth.a[0][2] + a[2][1] * oth.a[1][2] + a[2][2] * oth.a[2][2]) % p;
		} else {
			ans = Mat(3, 1);
			ans.a[0][0] = (a[0][0] * oth.a[0][0] + a[0][1] * oth.a[1][0] + a[0][2] * oth.a[2][0]) % p;
			ans.a[1][0] = (a[1][0] * oth.a[0][0] + a[1][1] * oth.a[1][0] + a[1][2] * oth.a[2][0]) % p;
			ans.a[2][0] = (a[2][0] * oth.a[0][0] + a[2][1] * oth.a[1][0] + a[2][2] * oth.a[2][0]) % p;
		}
		return ans;
	}

	bool operator == (const Mat &oth) const {
		if (n != oth.n || m != oth.m) return false;
		rep(i, n) rep(j, m) if (a[i][j] != oth.a[i][j]) return false;
		return true;
	}
};

Mat pow(Mat x, int e) {
	Mat ans = Mat(x.n, x.m);
	rep(i, x.n) ans.a[i][i] = 1;
	for (; e; e >>= 1, x = x * x)
		if (e & 1) ans = ans * x;
	return ans;
}

size_t get_hash(int x) {
	return x;
}

size_t get_hash(Mat x) {
	return (size_t)x.a[0][0] * p + x.a[1][0];
}

template <class T1, class T2>
struct HashMap {
	static const int siz = 1000003;
	int head[siz];
	vector <int> nex;
	vector <T1> key;
	vector <T2> val;
	int tot;

	void clear() {
		memset(head, -1, sizeof(head));
		nex.clear();
		key.clear();
		val.clear();
		nex.reserve(blk * blk * blk);
		key.reserve(blk * blk * blk);
		val.reserve(blk * blk * blk);
		tot = 0;
	}

	bool count(T1 x) {
		int id = get_hash(x) % siz;
		for (int e = head[id]; ~e; e = nex[e])
			if (key[e] == x) return true;
		return false;
	}

	T2 &operator [] (T1 x) {
		int id = get_hash(x) % siz;
		for (int e = head[id]; ~e; e = nex[e])
			if (key[e] == x) return val[e];
		nex.pb(head[id]);
		head[id] = tot;
		key.pb(x);
		val.pb(T2());
		return val[tot ++];
	}
};

HashMap <Mat, int> blks;
int per;
vector <int> ps;

ll qry(ll n) {
	return ps.size() * (n / per) + lower_bound(ps.begin(), ps.end(), n % per) - ps.begin();
}

void Main() {
	Mat temp;
	scanf("%d %d %d %d %d %d %d %d", &a, &b, &x, &y, &z, &p, &c, &q);
	if (y == 0) {
		HashMap <int, int> tim;
		tim.clear();
		int nw = b;
		int t = 0;
		while (!tim.count(nw)) {
			tim[nw] = t ++;
			nw = (nw * x + z) % p;
		}
		per = t - tim[nw];
		ps.clear();
		for (int u = b, cnt = 0; cnt < tim[nw]; ++ cnt) {
			if (u == c) ps.pb(cnt);
			u = (u * x + z) % p;
		}
		int PS = -1;
		for (int u = nw, cnt = 0; cnt < per; ++ cnt) {
			if (u == c) PS = cnt;
			u = (u * x + z) % p;
		}
		while (q --) {
			ll l, r;
			scanf("%lld %lld", &l, &r);
			-- l;
			auto S = [&] (ll n) {
				ll ans = 0;
				if (PS != -1) {
					if (n - 1 > tim[nw]) {
						ans += (n - 1 - tim[nw]) / per;
						ans += (n - 1 - tim[nw]) % per > PS;
					}
				}
				if (n > 1) ans += lower_bound(ps.begin(), ps.end(), n - 1) - ps.begin();
				if (n > 0) ans += a == c;
				return ans;
			};
			printf("%lld\n", S(r) - S(l));
		}
		return ;
	}
	Mat I = Mat(3, 3);
	rep(i, 3) I.a[i][i] = 1;
	Mat ini = Mat(3, 1);
	ini.a[0][0] = b;
	ini.a[1][0] = a;
	ini.a[2][0] = 1;
	Mat trans = Mat(3, 3);
	trans.a[0][0] = x; trans.a[0][1] = y; trans.a[0][2] = z;
	trans.a[1][0] = 1; trans.a[1][1] = 0; trans.a[1][2] = 0;
	trans.a[2][0] = 0; trans.a[2][1] = 0; trans.a[2][2] = 1;
	Mat transb = pow(trans, blk), transbb = pow(trans, blk * blk);
	per = -1;
	temp = ini;
	blks.clear();
	rep(i, blk * blk) {
		if (!blks.count(temp)) blks[temp] = i;
		else {
			per = i - blks[temp];
			break;
		}
		temp = trans * temp;
	}
	rep(i, blk * blk) {
		if (per == -1 && blks.count(temp)) {
			per = blk * blk + i * blk * blk - blks[temp];
			break;
		}
		temp = transbb * temp;
	}
	// eprintf("%d\n", per);
	temp = ini;
	blks.clear();
	rep(i, blk * blk * blk) {
		if (!blks.count(temp)) blks[temp] = i * blk;
		temp = transb * temp;
	}
	ps.clear();
	rep(d, p) {
		temp = Mat(3, 1);
		temp.a[0][0] = d;
		temp.a[1][0] = c;
		temp.a[2][0] = 1;
		rep(i, blk) {
			if (blks.count(temp)) {
				ps.pb((blks[temp] - i) % per);
				break;
			}
			temp = trans * temp;
		}
	}
	sort(ps.begin(), ps.end());
	ps.erase(unique(ps.begin(), ps.end()), ps.end());
	while (q --) {
		ll ql, qr;
		scanf("%lld %lld", &ql, &qr);
		-- ql;
		printf("%lld\n", qry(qr) - qry(ql));
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T --) Main();
	return 0;
}
