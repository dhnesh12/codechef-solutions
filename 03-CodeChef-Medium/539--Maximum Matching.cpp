#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef pair<ll ,ll> pll;
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define all(X) (X).begin(), (X).end()
#define REP(i,x,y) for(ll i = x;i <= y;++i)
#define fastio ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
vector<string> vec_splitter(string s) {
    for(char& c: s) c = c == ','?  ' ': c;
    stringstream ss; ss << s;
    vector<string> res;
    for(string z; ss >> z; res.push_back(z))
        ;
    return res;
}
void debug_out(vector<string> args, int idx) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, Head H, Tail... T) {
    if(idx > 0) cerr << ", ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, T...);
}
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __VA_ARGS__)
void localTest() {
    #ifndef ONLINE_JUDGE
        freopen("inp", "r", stdin);
        freopen("out", "w", stdout);
    #endif      
}
const ll N = 2e3 + 5;
ll dp[N], ans[N], po[N];
int main() {

    localTest();
    fastio;
    ll t, mod;
    cin >> t >> mod;
    po[0] = 1;
    for(ll i = 1; i < N; ++i) {
        po[i] = (2 * po[i - 1]) % mod;
    }
    for(ll i = 2; i < N; ++i) {
        for(ll j = 1; j < i; ++j) {
            dp[i] = (dp[i] + dp[i - j] + po[i - j - 1] * j * (i - j) % mod) % mod; 
        }
    } 
    for(ll i = 2; i < N; ++i) {
        for(ll j = 1; j < i; ++j) {
            ll sa = j * (i - j) % mod;
            sa = ((sa * sa % mod) * po[i - j - 1]) % mod;
            ll sb = (2 * j * ((i - j) * dp[i - j] % mod)) % mod;
            ans[i] = ((ans[i] + ans[i - j]) % mod + (sa + sb) % mod) % mod;
        }
    }
    while(t--) {
        ll n;
        cin >> n;
        cout << ans[n] << "\n";
    }


    return 0;
}