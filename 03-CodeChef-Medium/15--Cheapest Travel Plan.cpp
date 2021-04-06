#include <bits/stdc++.h>
using namespace std;
#define MX 300
int a[MX + 5], dist[MX + 5][MX + 5], d[MX + 5][MX + 5][MX + 5];

struct node {
	int c, p, d;
	node(int c, int p, int d): c(c), p(p), d(d) {}
	bool operator<(const node &b) const {
		return (c < b.c || (c == b.c && p < b.p) || (c == b.c && p == b.p && d < b.d));
	}
};

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m, cp, cd, pp, pd;
		scanf("%d%d%d%d%d%d", &n, &m, &cp, &cd, &pp, &pd);

		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			for (int j = 1; j <= n; j++)	dist[i][j] = 1e9;
			dist[i][i] = 0;
		}
		a[n] = 3;

		while (m--) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			dist[a][b] = c;
		}
		//Floyd-Warshall

		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= MX; j++) {
				for (int k = 0; k <= MX; k++)
					d[i][j][k] = 1e9;
			}
		}

		set<pair<int, node> > s;
		node init(1, (a[1] & 1) ? cp : 0, (a[1] & 2) ? cd : 0);
		s.insert({init.p * pp + init.d * pd, init});
		d[1][init.p][init.d] = init.p * pp + init.d * pd;
		int ans = 1e9;

		while (!s.empty()) {
			int cost = s.begin()->first;
			node cur = s.begin()->second;
			s.erase(s.begin());
			if (d[cur.c][cur.p][cur.d] != cost)
				continue;

			if (cur.c == n)
				ans = min(ans, cost - cur.p * pp - cur.d * pd); //Sell the remaining fuel

			for (int i = 1; i <= n; i++) {
				if (i == cur.c || !a[i] || cur.p + cur.d < dist[cur.c][i]) //Throw type-0 cities and cities you can't reach
					continue;
				node ns = cur;
				ns.c = i;
				if (a[i] == 1 || (a[i] == 3 && pp <= pd)) { //Petrol city or petrol is cheaper, finish petrol first
					if (dist[cur.c][i] <= ns.p)
						ns.p -= dist[cur.c][i];
					else {
						ns.d -= (dist[cur.c][i] - ns.p);
						ns.p = 0;
					}
				}
				else { //Diesel city or diesel is cheaper, finish diesel first
					if (dist[cur.c][i] <= ns.d)
						ns.d -= dist[cur.c][i];
					else {
						ns.p -= (dist[cur.c][i] - ns.d);
						ns.d = 0;
					}
				}

				int nc = cost;
				if (a[i] & 1) { //can buy petrol, fill the petrol tank
					nc += (cp - ns.p) * pp;
					ns.p = cp;
				}

				if (a[i] & 2) {//can buy diesel, fill the diesel tank
					nc += (cd - ns.d) * pd;
					ns.d = cd;
				}

				if (nc < d[ns.c][ns.p][ns.d]) {
					d[ns.c][ns.p][ns.d] = nc;
					s.insert({nc, ns});
				}
			}
		}

		if (ans == 1e9)	ans = -1;
		printf("%d\n", ans);
	}
}
