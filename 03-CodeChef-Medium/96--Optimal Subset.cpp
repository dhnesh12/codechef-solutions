#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const int Maxn = 100005;

int t;
int n;
int w[Maxn];
int X[Maxn], Y[Maxn];

ld Len(int a, int b) { return sqrt(ld(X[a] - X[b]) * (X[a] - X[b]) + ld(Y[a] - Y[b]) * ld(Y[a] - Y[b])); }

bool Ok(ld E)
{
	ld res = 0;
	vector <int> seq;
	seq.push_back(0);
	vector <ld> dist;
	for (int i = 1; i < n; i++) {
		while (seq.size() >= 2)
			if (Len(seq[int(seq.size()) - 2], i) - Len(seq.back(), i) >= dist.back() - E * w[seq.back()]) {
				res -= (dist.back() - E * w[seq.back()]);
				dist.pop_back(); seq.pop_back();
			} else break;
		dist.push_back(Len(seq.back(), i));
		seq.push_back(i);
		res += dist.back() - E * w[seq.back()];
		if (res + Len(0, i) - E * w[0] >= 0) return true;
	}
	return false;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &X[i], &Y[i]);
		for (int i = 0; i < n; i++)
			scanf("%d", &w[i]);
		ld lef = 0, rig = 10e15l;
		for (int i = 0; i < 80; i++) {
			ld mid = (lef + rig) / 2.0l;
			if (Ok(mid)) lef = mid;
			else rig = mid;
		}
		cout << fixed << setprecision(9) << lef << endl;
	}
	return 0;
}