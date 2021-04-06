#include<bits/stdc++.h>
using namespace std;
const int nax = 1e6 + 5;
const int inf = 1e9 + 5;
int t[nax];
bool ok(int n, int forbid) {
	int previous = inf, diff = inf;
	for(int i = 1; i <= n; ++i) if(i != forbid) {
		if(previous != inf) {
			if(diff == inf) diff = t[i] - previous;
			else if(diff != t[i] - previous) return false;
		}
		previous = t[i];
	}
	return true;
}
void te() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &t[i]);
	int ans = inf;
	if(ok(n, 1)) ans = min(ans, t[1]);
	if(ok(n, 2)) ans = min(ans, t[2]);
	if(ok(n, n)) ans = min(ans, t[n]);
	int diff = t[2] - t[1];
	for(int i = 3; i <= n - 1; ++i)
		if(t[i] - t[i-1] != diff) {
			int maybe_remove = t[i];
			if(t[i+1] - t[i-1] != diff) break;
			bool suf_ok = true;
			for(int j = i + 2; j <= n; ++j)
				if(t[j] - t[j-1] != diff) suf_ok = false;
			if(suf_ok) ans = min(ans, maybe_remove);
			break;
		}
	if(ans == inf) ans = -1;
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) te();
}