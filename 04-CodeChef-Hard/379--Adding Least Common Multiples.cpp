// nlather (Nishant Raj Lather)
// Chrollo_Lucifer

/* ------------------------------ TEMPLATE BEGIN ------------------------------ */

#include <iostream>
// using namespace std;

// /* ----------------- ORDERED SET (POLICY BASED DS) ----------------- */
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <typename T>
// using ordered_set = tree
//     <T, null_type, less<T>, rb_tree_tag, 
//     tree_order_statistics_node_update>;

// /* -------------- BETTER RANDOM (RAND() IS DANGEROUS) -------------- */
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// #define rnd(x, y) uniform_int_distribution<ll>(x, y)(rng)

// /* ----------------- CUSTOM HASH FUNCTION FOR UMAP ----------------- */
// struct custom_hash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = 
//             chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };

// /* ----------------------- DEBUGGING UTILITY ----------------------- */
// #define cerr cout
// void _print() {cerr << "]\n";}
// template <typename T, typename... V> void _print(T t, V... v) {
//     cerr << t; if(sizeof...(v)) cerr << ", "; _print(v...);
// }
// #define debug(x...) cerr << "[" << #x << "] = ["; _print(x)

#define boost ios_base::sync_with_stdio(false);cin.tie(nullptr);
#define rep(i, x, n) for (ll i = (ll)(x); i < (ll)(n); i++)
// #define rrep(i, x, n) for (ll i = (ll)(x); i >= (ll)(n); i--)
// #define all(v) v.begin(), v.end()
// #define rall(v) v.rbegin(), v.rend()
// #define ff first
// #define ss second
// #define pb push_back
// #define eb emplace_back
// #define mp make_pair
// #define bs binary_search
// #define minSelf(a, b) a = min(a, b)
// #define maxSelf(a, b) a = max(a, b)
// #define mem(arr, x) memset(arr, x, sizeof(arr))
// using ll = long long int;
// using ld = long double;
// template <typename T, typename V> using P = pair<T, V>;
// template <typename T> using V = vector<T>;
// const ll MOD = 998244353LL;
// const ll INF = 0x3f3f3f3f; // ~1e9 (1061109567)
// const ld PI = 3.1415926535897932384626;
// const ld EPS = 1e-9;
#define endl '\n' // REMOVE FOR INTERACTIVE TASKS
#define ll long long int
const ll MAX = 4e6+5;

/* ------------------------------- TEMPLATE END ------------------------------- */

const ll mod = (1LL<<30)-1;
ll f[MAX], mu[MAX], comp[MAX], prm[MAX], sz = 0;

int main() {
    f[1] = 1, mu[1] = 1;
    rep(i, 2, MAX) {
        if(!comp[i]) prm[sz++] = i, f[i] = 1-i, mu[i] = -1;
        for(ll j = 0; j < sz && i*prm[j] < MAX; j++) {
            comp[i*prm[j]] = 1;
            if(i%prm[j] == 0) {
                if((i/prm[j])%prm[j])
                    f[i*prm[j]] = -prm[j] * f[i/prm[j]];
                else f[i*prm[j]] = 0;
                mu[i*prm[j]] = 0;
                break;
            } else {
                f[i*prm[j]] = f[i] * f[prm[j]];
                mu[i*prm[j]] = mu[i] * mu[prm[j]];
            }
        }
    }
    rep(i, 1, MAX) f[i] = i * f[i] + f[i-1];
    ll t, a, b;
    scanf("%lli", &t);
    while(t--) {
        scanf("%lli%lli", &a, &b);
        if(a > b) std::swap(a, b);
        ll ans = 0;
        for(ll i = 1, la; i <= a; i = la + 1) {
            la = std::min(a / (a / i), b / (b / i));
            ll temp = (f[la] - f[i-1] + mod + 1) & mod;
            temp = (temp * (((a/i)*(1+a/i)/2LL)&mod)) & mod;
            temp = (temp * (((b/i)*(1+b/i)/2LL)&mod)) & mod;
            ans = (ans + temp + mod + 1) & mod;
        }
        printf("%lli\n",ans);
    }
}
