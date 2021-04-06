#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long int
#define sd(x) scanf("%lld",&x)
#define inf 10000000000000000ll
#define pll pair<ll,ll>
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define bits(x) __builtin_popcountll(x)
#define ld long double
#define test() ll test; cin>>test; while(test--)
#define fi first
#define se second


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


inline ll GCD(ll x, ll y) {
    if(x<y) swap(x,y);
    if(x==0) return y;
    if(y==0) return x;
    return GCD(x%y,y);
}

ll phi(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}

ll power(ll x, ll n, ll mod) {
    ll res = 1;
    x %= mod;
    while(n) {
        if(n&1) {
            res = ((res*x)%mod+mod)%mod;
        }
        x = ((x*x)%mod+mod)%mod;
        n>>=1;
    }

    return res;
}


inline bool check(ll a, ll b, ll c) {
    return (a!=b)+(b!=c)+(c!=a) < 3;
}

int main() {
    fastio;
    test() {
        ll N;
        cin>>N;

        vector<vector<vector<ll> > > dp(N+5,vector<vector<ll> >(5,vector<ll>(5,inf)));

        vector<ll> A(N+5,0);

        for(int i=1;i<=N;i++) cin>>A[i];

        if(N<=2) {
            cout<<0<<endl;
            continue;
        }

        for(int cur=-1;cur<=1;cur++) {
            for(int lst=-1;lst<=1;lst++) {
                dp[2][cur+1][lst+1] = (cur!=0)+(lst!=0);
            }
        }

        for(int i=3;i<=N;i++) {
            for(int cur=-1;cur<=1;cur++) {
                for(int lst=-1;lst<=1;lst++) {
                    for(int prv=-1;prv<=1;prv++) {
                        if(check(A[i-2+prv],A[i-1+lst],A[i+cur]))
                        dp[i][cur+1][lst+1] = min(dp[i][cur+1][lst+1],dp[i-1][lst+1][prv+1]+(cur!=0));
                    }
                }
            }
        }

        ll ans = inf;
        for(int cur=-1;cur<=1;cur++) {
            for(int lst=-1;lst<=1;lst++) {
                ans = min(ans,dp[N][cur+1][lst+1]);
            }
        }

        cout<<ans<<endl;
    }

}




