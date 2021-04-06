#include<bits/stdc++.h>
using namespace std;
using  ll  = long long;
using  ld  = long double;
using pli  = pair<ld,int>;
using ring = tuple<ll,ll,ll>;
using cp   = complex<ld>;

const int N = 90, P = 60; const ll f_max = -1LL << P, g_min = 1LL << P;

const ld eps = 1e-6, one = 1, pi = acos(-one), k = pi/N, l = k/2, v = cos(l);

int q, m, op, ans; ld d, r, u, w, s[N],t[N]; pli f[N], g[N]; vector<ring> a; ll x, y, c;

inline bool outside(const ring &z) { ll dx = x-get<0>(z), dy = y-get<1>(z); return dx*dx+dy*dy > get<2>(z); }  

inline void add_ring() {
	cin >> c, r = sqrt(c), a.emplace_back(x,y,c);
	for (int m = a.size()-1, i = 0; i < N; ++i)
		u = y+x*t[i], d = r*v*s[i],
		f[i] = max(f[i],{u-d,m}),
		g[i] = min(g[i],{u+d,m}); }
	
inline int success() {
	ans = 1;
	for (int i = 0; i < N; ++i) {
		u = y+x*t[i];
		if (f[i].first > u-eps) {
			if (outside(a[f[i].second])) { ans = 0; break; } }
		if (g[i].first < u+eps) {
			if (outside(a[g[i].second])) { ans = 0; break; } } }
	return ans; }	
	
int main() 
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr), cin >> q;
	
	for (int i = 0; i < N; ++i) 
		f[i].first = f_max, g[i].first = g_min;
		
	for (int i = 0; i < N; ++i) 
		w = k*i+l, s[i] = one/sin(w), t[i] = s[i]*cos(w);
		
	while (q--) 
	{
		if (cin >> op >> x >> y, ans)
			swap(x,y);
			
		if (op == 1) 
			add_ring();
		else
			cout << success() << '\n'; 
	} 
}