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
typedef long double ld;
typedef pair <int, int> ii;

const ll Inf = 9000000000000000000ll;
const int Maxm = 52;
const int Maxn = 1005;

int t;
int n;
int fav[Maxn];
ii seq[Maxn];
int k;
int a[Maxm];
ll mn[Maxm];
ll res[Maxn];

ll getNext(ll from)
{
	while (mn[from % a[0]] > from) from++;
	return from;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &fav[i]);
			seq[i].first = fav[i]; seq[i].second = i;
		}
		sort(seq, seq + n);
		scanf("%d", &k);
		for (int i = 0; i < k; i++)
			scanf("%d", &a[i]);
		sort(a, a + k);
		fill(mn, mn + a[0], Inf);
		mn[0] = 0;
		priority_queue <ii> Q; Q.push(ii(-mn[0], 0));
		while (!Q.empty()) {
			int v = Q.top().second, d = -Q.top().first; Q.pop();
			if (d != mn[v]) continue;
			for (int i = 0; i < k; i++) {
				int u = (v + a[i]) % a[0];
				if (d + a[i] < mn[u]) {
					mn[u] = d + a[i]; Q.push(ii(-mn[u], u));
				}
			}
		} 
		for (int i = 0; i < n; i++) {
			int ind = seq[i].second;
			ll small = 0;
			if (ind > 0 && fav[ind - 1] < fav[ind]) small = max(small, 2 * res[ind - 1] + 1);
			if (ind + 1 < n && fav[ind + 1] < fav[ind]) small = max(small, 2 * res[ind + 1] + 1);
			res[ind] = getNext(small);
		}
		ll sum = 0;
		for (int i = 0; i < n; i++)
			sum += res[i];
		cout << fixed << setprecision(6) << ld(sum) / ld(n) + 1e-11l << endl;
	}
	return 0;
}