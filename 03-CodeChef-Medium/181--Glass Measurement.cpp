#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair <ll, int> lli;

const int Maxn = 11;
const ll Inf = 9000000000000000000ll;
const int Maxm = 100005;

int t;
int n;
int A[Maxn];
ll dist[Maxm];
int q;

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		sort(A, A + n);
		fill(dist, dist + Maxm, Inf); dist[0] = 0;
		priority_queue <lli> Q; Q.push(lli(-dist[0], 0));
		while (!Q.empty()) {
			int v = Q.top().second;
			ll d = -Q.top().first; Q.pop();
			if (d != dist[v]) continue;
			for (int i = 1; i < n; i++) {
				int u = (v + A[i]) % A[0];
				if (d + A[i] < dist[u]) {
					dist[u] = d + A[i]; Q.push(lli(-dist[u], u));
				}
			}
		}
		ll res = -1;
		for (int i = 0; i < A[0]; i++)
			if (dist[i] < Inf) res = max(res, dist[i] - A[0]);
		if (res >= Inf) printf("-1\n");
		else printf("%lld\n", res);
		scanf("%d", &q);
		ll a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
		int ok = 0;
		for (int i = 1; i <= q; i++) {
			ll m = (a * i + b) % c;
			ok += dist[m % A[0]] <= m;
		}
		printf("%d %d\n", q - ok, ok);
	}
	return 0;
}
