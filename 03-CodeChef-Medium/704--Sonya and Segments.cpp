#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

#define x first
#define y second
#define ndl '\n'
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define up_b upper_bound
#define low_b lower_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

using namespace std;
//using namespace __gnu_pbds;

//template<typename T> using indexed_set = tree <T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());//uniform_int_distribution<int> (l, r)

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<int, ull> piu;
typedef vector<vector<int>> matrix;

const ll INF = 1e18 + 123;
const ld EPS = 1e-9;
const int inf = 1e9 + 123;
const int MOD = 1e9 + 7;
const int N = 4e5 + 123;
const int M = 1e6 + 123;
const double pi = 3.14159265359;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int binpow(int a, int b){
    int res = 1;
    while (b){
        if (b&1){
            res = 1ll*res*a % MOD;
        }
        a = 1ll*a*a % MOD;
        b >>= 1;
    }
    return res;
}

int f[N], invf[N];

int cnk(int n, int k){
    if (n < k) return 0;
    int res = f[n];
    res = 1ll*res*invf[k] % MOD;
    res = 1ll*res*invf[n-k] % MOD;
    //cout << n << " " << k << " " << res << ndl;
    return res;
}

int l[N], r[N];

void solve(){
    int n = rng()%10+1, k = rng()%n+1;
    //cout << n << " " << k << ndl;
    cin >> n >> k;
    vector<pii> ev;
    for (int i = 1; i <= n; i++){
        //l[i] = rng()%12+1;
      //  r[i] = rng()%12+1;
        cin >> l[i] >> r[i];
        if (l[i] > r[i]) swap(l[i], r[i]);
        //cout << l[i] << " " << r[i] << ndl;
        ev.pb({l[i], 1});
        ev.pb({r[i]+1, -1});
    }
   // cout << endl;
    int cnt = 0, ans = cnk(n, k);
    sort(all(ev));
    for (pii p : ev){
        cnt += p.y;
        if (p.y == -1){
            ans -= cnk(cnt, k-1);
            if (ans < 0) ans += MOD;
        }
    }
    cout << ans << endl;
   

    return;
}

int main(){
    f[0] = invf[0] = 1;
    for (int i = 1; i < N; i++){
        f[i] = 1ll*i*f[i-1] % MOD;
        invf[i] = binpow(f[i], MOD-2);
    }
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++){
        //cout << "Case #" << i << ": ";
        solve();
    }
    #ifdef KAZAKH
      //  cout << endl << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    #endif
    return 0;
}