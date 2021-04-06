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
	int T;
	
	cin >> T;

	while(T--){
		ll n; cin >> n;

		n = poww(2, n, MOD);

		n = (n - 1 + MOD) % MOD;

		cout << n << endl;
	}

	return 0;
}


