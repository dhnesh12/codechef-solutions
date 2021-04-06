#define DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
using namespace std;
 
#define F first
#define S second
#define fi first
#define sc second
#define pb push_back
#define endl "\n"

#define IOS { ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0); }

#ifdef DEBUG
    #define dbg(s) {s;}
#endif

#ifndef DEBUG
    #define dbg(s)
#endif

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int grand(int x) { // from [0, x-1]
    return uniform_int_distribution<int>(0, x - 1)(rng);
}

#define int ll
#define i32 int32_t

#define RBTTYPE int
#define ordered_set tree<RBTTYPE, null_type, less<RBTTYPE>, rb_tree_tag,tree_order_statistics_node_update> 

#define all(v) (v).begin(),(v).end()

typedef long long ll;
typedef long double ld;
typedef pair< int, int > pii;
typedef pair< ll, ll > pll;

int getInt () {
    bool minus = false;
    int result = 0;
    char ch;
    ch = getchar();
    while (true) {
        if (ch == '-') break;
        if (ch >= '0' && ch <= '9') break;
        ch = getchar();
    }
    if (ch == '-') minus = true; else result = ch-'0';
    while (true) {
        ch = getchar();
        if (ch < '0' || ch > '9') break;
        result = result*10 + (ch - '0');
    }
    if (minus)
        return -result;
    else
        return result;
}


ll gcd(ll x, ll y) {
    if (x < y) return gcd(y, x);
    if (y == 0) return x;
    return gcd(y, x % y);
} 

const ll mod = 1e9 + 7;

ll modexp(ll x, ll ex) {
    ll ans = 1ll;
    while (ex > 0) {
        if (ex & 1ll) ans = (ans * x) % mod;
        ex >>= 1ll;
        x = (x * x) % mod;
    }
    return ans;
}

const int maxn = 1e6 + 7;
const int N = 2e5 + 7;

const ll inf = 1e9 + 7;

int phi[N];
int fc[N];
int ifc[N];
vector < int > prm;
int is_com[N];
int ans[N];

int ncr(int n, int r){
    if(r > n) return 0;
    return (((fc[n]*ifc[r])%mod)*ifc[n-r])%mod;
}

i32 main() {
    //freopen("<file>.in", "r", stdin);
    //freopen("<file>.out", "w", stdout);

    IOS;

    int q, k; cin >> q >> k;
   
    phi[1] = 1; 
    for(int i = 2; i < N; i++){
        if(!is_com[i]){
            prm.pb(i);
            phi[i] = i - 1;
        }
        for(auto j : prm){
            if(i*j > N) break;
            is_com[i*j] = 1;
            if(i%j == 0){
                phi[i*j] = j*phi[i];
                break;
            }else{
                phi[i*j] = phi[j]*phi[i];
            }
        }
    }

    fc[0] = 1;
    for(int i = 1; i < N; i++){
        fc[i] = (fc[i-1]*i)%mod;
    }
    ifc[N-1] = modexp(fc[N-1], mod - 2);
    for(int i = N - 2; i >= 0; i--){
        ifc[i] = ((i+1)*ifc[i+1])%mod;
    }

    for(int i = 1; i < N; i++){
        for(int j = 0; j < N; j += i){
            ans[j] = (((ncr(j/i, k)*phi[i])%mod) + ans[j])%mod;
            if(j + i < N) ans[i + j] =  (mod - ((ncr(j/i, k)*phi[i])%mod) + ans[i + j])%mod;
        }
    }

    for(int i = 1; i < N; i++){
        ans[i] = (ans[i-1] + ans[i])%mod;
    }

    for(int i = 1; i < N; i++){
        if(i-k >= 0) ans[i] = ((((((ans[i]*fc[k])%mod)*fc[i-k])%mod)*ifc[i])%mod);
        else ans[i] = 0;
    }

    
    for(int i = 0; i <= 10 ; i++){
        //cout << i << " " << phi[i] << " " << ans[i] << " " << fc[i] << " " << ifc[i] << endl;
    }

    while(q--){
        int n; cin >> n;
        cout << ans[n] << endl;
    }
    
}