#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair <int, int> pii;
 
#define all(x)			(x).begin(), (x).end()
#define sz(x)			(int)((x).size())
#define X				first
#define Y				second
#define debug(x)		cerr << #x << " : " << x << endl;
#define fast_io			ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl            '\n'
 
ll poww(ll a, ll b, ll md) {
	return (!b ? 1 : (b & 1 ? a * poww(a * a % md, b / 2, md) % md : poww(a * a % md, b / 2, md) % md));
}
 
constexpr int N = 1e6 + 10;
const int MOD = 1e9 + 7;
const ll INF = 8e18;


int main(){
	fast_io
	int q; cin >> q;

	while(q--){
		int u, v; cin >> u >> v;
	
		if(u > v)
			swap(u, v);

		vector <int> a, b;

		for(; u; u /= 2)
			a.push_back(u);

		for(; v; v /= 2)
			b.push_back(v);

		reverse(all(a)), reverse(all(b)); int ans = 0;

		for(int i = 0; i < sz(a); ++i){
			if(a[i] != b[i]){
				i--;
				ans = sz(a) - 1 - i + sz(b) - 1 - i;
				goto eden;
			} else if(i == sz(a) - 1){
				ans = sz(b) - 1 - i;
				goto eden;
			}
		}

		eden:
			cout << ans << endl;

	}

	return 0;
}


