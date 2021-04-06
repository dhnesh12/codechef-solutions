#pragma GCC optimization "Ofast"
#pragma GCC optimization "unroll-loop"
#pragma GCC target ("avx2")

#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define fs first
#define sc second
using namespace std;
const ll N = 1e6 + 9;
const ll inf = 1e9 + 7;
typedef pair<ll,ll> LL;
vector<ll> v;
ll n,x,dp[N],k;

ll nxt(ll x){
    return lower_bound(v.begin(),v.end(),x) - v.begin();
}

ll f(ll pos){
    if (pos == n) return 0;
    if (dp[pos] != -1) return dp[pos];
    ll p = nxt(v[pos] + k);
    return dp[pos] = f(p) + 1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #define task "test"
    if (fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        //freopen(task".out","w",stdout);
    }
    cin>>n>>k; memset(dp,-1,sizeof(dp));
    for (ll i = 1;i <= n;i++) cin>>x,v.push_back(x); v.push_back(inf);
    sort(v.begin(),v.end()); //cout<<nxt(4); return 0;
    cout<<f(0);
}
