#include <bits/stdc++.h>
#define va first
#define vb second
#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define pp push_back
#define ep emplace_back
#define all(v) (v).begin(),(v).end()
#define szz(v) ((int)(v).size())
#define bi_pc __builtin_popcount
#define bi_pcll __builtin_popcountll
#define bi_tz __builtin_ctz
#define bi_tzll __builtin_ctzll
#define fio ios_base::sync_with_stdio(0);cin.tie(0);
#ifdef TAMREF
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) 42
#endif
using namespace std;
using ll = long long; using lf = long double; 
using pii = pair<int,int>; using ppi = pair<int,pii>;
using pll = pair<ll,ll>; using pff = pair<lf,lf>;
using ti = tuple<int,int,int>;
using base = complex<double>;
const lf PI = 3.14159265358979323846264338L;
template <typename T>
inline T umax(T& u, T v){return u = max(u, v);}
template <typename T>
inline T umin(T& u, T v){return u = min(u, v);}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<ll> g({0});
const ll MX = 2e10;
ll n, k;

int nCr(ll n, ll r){
    return !(bi_pcll(r) + bi_pcll(n - r) - bi_pcll(n));
}

int main(){
    fio;
    for(ll x = 1; x * (3*x - 1) / 2 <= MX; x++){
        g.pp(x*(3*x - 1) / 2);
        g.pp(x*(3*x + 1) / 2);
    }
    int t;
    for(cin >> t; t--;){
        cin >> n >> k;
        int ans = 0;
        for(ll x : g){
            if(x > k) break;
            ll r = k - x;
            ans ^= nCr(n + r - 1, r);
        }
        cout << ans << '\n';
    }
}