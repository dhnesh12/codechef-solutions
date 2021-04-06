#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back
#define f first
#define s second

const int mod = 1e9 + 7;

vector<pair<ll,ll>>arr;

ll dp[2000005],fact[9000005],inv[9000005];

ll power(ll a,ll b){
    ll ans = 1;
    while(b){
        if(b&1) ans = (ans*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return ans;
}

void precompute() {
    fact[0] = 1;
    inv[0] = 1;
    for(ll i=1;i<9000005;i++) fact[i] = (fact[i-1]*i)%mod;
    inv[9000004] = power(fact[9000004],mod-2);
    for(ll i= 9000003;i>=1;i--) {
        inv[i] = (inv[i+1]*(i+1))%mod;
    }
}

ll catalan(ll m,ll n){
    if(m<0 || n<0) return 0;
    ll  ans = fact[m+n];
    ans = (ans*inv[m])%mod;
    ans = (ans*inv[n])%mod;
    return ans;
}

ll f(ll x1,ll y1,ll x2,ll y2,ll c){
    ll tempx = y1+c-1;
    ll tempy = x1-c+1;
    ll ans = (catalan(x2-x1,y2-y1)-catalan(x2-tempx,y2-tempy) + mod)%mod;
    return ans;
}

int main() {
    precompute();
    ll p,q,c,m;
    cin>>p>>q>>c>>m;
    bool flag = p-q < c;
    ll x,y;
    for(int i=0;i<m;i++) {
        cin>>x>>y;
        if(x-y >= c && x<=p && y<=q) arr.pb(mp(x,y));
        if(x<=c && y==0) flag = 1;
        if(x==p && y==q) flag = 1;
    }
    arr.pb(mp(p,q));
    if(flag) {
        cout<<0<<endl;
        return 0;
    }
    sort(arr.begin(),arr.end());
    arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
    for(int i=0;i<arr.size();i++) {
        dp[i] = f(c,0,arr[i].f,arr[i].s,c);
        //cout<<dp[i]<<endl;
        for(int j=0;j<i;j++) {
            if(arr[j].f>arr[i].f || arr[j].s>arr[i].s) continue;
            ll temp = (f(arr[j].f,arr[j].s,arr[i].f,arr[i].s,c)*dp[j])%mod;
            dp[i] -= temp;
            if(dp[i]<0) dp[i] += mod;
        }
    }
    cout<<dp[arr.size()-1];
}