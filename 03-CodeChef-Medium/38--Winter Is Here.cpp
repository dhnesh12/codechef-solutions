#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int MAX = 1000 * 1000 * 1000, SQRTMAX = 31623, MAXD = 1350;
vector<int> p;

int sv[SQRTMAX];
map<int, int> m;

const int N = 100010;

int ft[MAXD][N];

void upd(int id, int pos, int val)
{
	while (pos < N)
	{
		ft[id][pos] += val;
		pos += pos&-pos;
	}
}

int query(int id, int pos)
{
	int ret = 0;
	while (pos)
	{
		ret += ft[id][pos];
		pos -= pos&-pos;
	}
	return ret;
}

int ftx[N];
void updxor(int pos, int val)
{
	while (pos < N)
	{
		ftx[pos] ^= val;
		pos += pos&-pos;
	}
}

int queryxor(int pos)
{
	int ret = 0;
	while (pos)
	{
		ret ^= ftx[pos];
		pos -= pos&-pos;
	}
	return ret;
}

int ans[2*N];

int main()
{
	for (int i = 2; i < SQRTMAX; i++)
	{
		if (sv[i]) continue;
		p.pb(i);
		for (int j = i*i; j < SQRTMAX; j += i)
			sv[j] = i;
	}

	int n;
	scanf("%d", &n);
	vector<tuple<int, int, int> > v;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		if (!m.count(y))
		{
			int cnt = 1;
			int yy = y;
			for (int j = 0; j < p.size() and p[j] * p[j] <= yy; j++)
			{
				int f = 0;
				while (yy % p[j] == 0)
				{
					yy /= p[j];
					f++;
				}
				cnt *= (f+1);
			}
			if (yy != 1)
				cnt *= 2;
			m[y] = cnt;
		}
		v.eb(x, m[y], i);
	}
	sort(v.begin(), v.end());
	int qc;
	scanf("%d", &qc);
	vector<tuple<int, int, int, int> > q;
	for (int i = 0; i < qc; i++)
	{
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		q.eb(k, l, r, i);
	}
	sort(q.begin(), q.end());
	
	int pos = 0;
	for (int i = 0; i < qc; i++)
	{
		int l, r, k, id;
		tie(k, l, r, id) = q[i];
		while (pos < n and get<0>(v[pos]) <= k)
		{
			int dy = get<1>(v[pos]), p = get<2>(v[pos]);
			upd(dy, p, 1);
			updxor(p, dy);
			pos++;
		}
		int x = queryxor(r)^queryxor(l-1);
		ans[id] = query(x, r) - query(x, l-1);	
	}
	for (int i = 0; i < qc; i++)
		printf("%d\n", ans[i]);
	return 0;
}

