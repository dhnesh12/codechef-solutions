#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include "bits/stdc++.h"
using namespace std;

#define all(x) (x).begin(), (x).end()
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define un_map unordered_map
#define rep(i,a,n) for (int i = a; i < n; ++i) 
#define rrep(i,a,n) for (int i = a; i >= n; --i) 
#define irep(i,a,n,inc) for (int i = a; i < n; i += inc) 
#define endl "\n"

typedef long long ll;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
 
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

#define int long long 

int k = 1e10 + 5;
int const mod = 1e9 + 7;

int32_t main() {
	IOS;
	vector<int> val(3e7); val[1] = 1;
	for (int i = 2, p = 1; p <= k; ++i) {
		val[i] = 1 + val[i - val[val[i - 1]]];
		p += val[i];
	}
	
	vector<int> sol(3e7);
	vector<int> cnt(3e7);cnt[1e7] = 1e11;
	rep(i, 1, 1e7) cnt[i] = cnt[i - 1] + val[i]; 
	rep(i, 1, 1e7) sol[i] = (sol[i - 1] + i * i % mod * val[i] % mod) % mod;
	
	auto upper_bound = [&](int p)->int{
		int l = 0;
		int r = 1e7;
		while (l < r) {
			int mid = (l + r) / 2;
			if (cnt[mid] > p) r = mid;
			else l = mid + 1;
		}
		return l;
	};
	//rep(i, 0, 30) cout << cnt[i] << " ";
	//cout << endl;
	//rep(i, 0, 30) cout << sol[i] << " ";
	//cout << endl;
	auto find = [&](int des)->int {
		int index = upper_bound(des);
		int left = des - cnt[index - 1];
		//cout << index << " " << left << endl;
		return (sol[index - 1] + (index * index) % mod * left % mod) % mod;
	};
	int TC; cin >> TC; 
	while (TC--) {
		int l, r; cin >> l >> r;
		cout << (find(r) - find(l - 1) + mod) % mod << endl;
	}
}












