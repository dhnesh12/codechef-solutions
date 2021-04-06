#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int Maxn = 300005;
const int Inf = 1000000007;
const ll bInf = 4000000000000000000ll;
 
int n;
int S[Maxn], T[Maxn];
int mx = Inf;
int q;
 
ll Get(int len)
{
	ll sumS = 0;
	for (int i = 0; i < n; i++)
		sumS += S[i];
	ll res = sumS - ll(n) * S[0];
	int pnt = 0;
	ll sumT = 0;
	for (int i = 0; i < n; i++) {
		sumT += T[i] - len;
		while (pnt < n && T[i] - len >= S[pnt]) {
			sumS -= S[pnt]; pnt++;
		}
		res = min(res, ll(i + 1) * (T[i] - len) - sumT + sumS - ll(n - pnt) * (T[i] - len));
	}
	res = min(res, ll(n) * (T[n - 1] - len) - sumT);
	pnt = n - 1;
	sumS = 0;
	for (int i = n - 1; i >= 0; i--) {
		sumS += S[i];
		while (pnt >= 0 && S[i] <= T[pnt] - len) {
			sumT -= (T[pnt] - len); pnt--;
		}
		res = min(res, sumS - ll(n - i) * S[i] + ll(pnt + 1) * S[i] - sumT);
	}
	return res;
}
 
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &S[i], &T[i]);
		mx = min(mx, T[i] - S[i]);
	}
	sort(S, S + n); sort(T, T + n);
	scanf("%d", &q);
	while (q--) {
		ll k; scanf("%lld", &k);
		int lef = 1, rig = mx;
		while (lef <= rig) {
			int mid = lef + rig >> 1;
			if (Get(mid) <= k) lef = mid + 1;
			else rig = mid - 1;
		}
		printf("%d\n", lef - 1);
	}
	return 0;
} 