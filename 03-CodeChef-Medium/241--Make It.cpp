/*/ Author---> adityapathak16 /*/
/*/ Copyright © 2020 Aditya Pathak. All rights reserved. /*/
/*/_____________________________________________08-08-2019_____I WILL NEVER FORGET__________________________________________/*/

#include "bits/stdc++.h"
#include <cstdio>
using namespace std;
#define ll long long
typedef vector<ll> vi;
typedef pair<ll,ll> pii;
typedef pair<pii,ll> ppi;
typedef vector<pii> vpi;
typedef priority_queue<ppi> max_heap_ppi;
#define For(i,n) for(ll i=0;i<(ll)n;i++)
#define Rev(i,n) for(ll i=n-1;i>=0;i--)
#define Rep(i,n) for(ll i=1;i<=n;++i)
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define endl "\n"
#define d0(x) cout<<(x)<<" "
#define d1(x) cout<<(x)<<endl
#define d2(x,y) cout<<(x)<<" "<<(y)<<endl
#define d3(x,y,z) cout<<(x)<<" "<<(y)<<" "<<(z)<<endl
#define d4(a,b,c,d) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<endl
#define d5(a,b,c,d,e) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<endl
#define d6(a,b,c,d,e,f) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<" "<<(e)<<" "<<(f)<<endl
#define fio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define all(v) (v).begin(),(v).end()
#define sz(v) (v).size()


template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ ";
    for(auto v : V) os << v << " ";
    return os << "]";
}
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ ";
    for(auto s:S) os<<s<<" ";
    return os<<"}";
}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.first << "," << P.second << ")";
}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {
    os << "{ ";
    for(auto m:M) os<<"("<<m.F<<":"<<m.S<<") ";
    return os<<"}";
}

#define TRACE
#ifdef TRACE
    #define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1>
    void __f(const char* name, Arg1&& arg1){
        cerr << name << " : " << arg1 << endl;
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ',');
        cerr.write(names, comma - names) << " : " << arg1<<" | ";
        __f(comma+1, args...);
    }
#else
    #define trace(...)
#endif
const ll maxn=1e5+100;
const ll MaxN=1e5+100;
const ll mod=1e9+7;
inline ll fast_expo(ll base,ll power,ll modulo=mod){
    base%=modulo;
    if (base<0) base+=modulo;
    ll x=base,cnt=power,ans=1;
    while(cnt){
        if (cnt&1) ans=(ans*x)%modulo;
        x=(x*x)%modulo;
        cnt>>=1;
    }
    return ans;
}
inline ll inv(ll base,ll modulo=mod){
    return fast_expo(base,modulo-2,modulo);
}
const ll INF=1e18;
const int MAX=1e8+2;
int idx[MAX];
ll A[maxn];


ll dp[maxn][800] ,dp2[maxn][800];

ll B[maxn];




vi GC[maxn];


void solve(){
    ll n,q,k;
    cin>>n>>q>>k;
    vi fac;
    
    for(ll i=1;i*i<=k;++i){
        if ((k%i)==0){
            fac.pb(i);
            if (i*i!=k) fac.pb(k/i);
        }
    }
    sort(all(fac));
    for(ll i=0;i<fac.size();++i){
        idx[fac[i]]=i;
    }
    Rep(i,n){
        cin>>A[i];
        B[i]=__gcd(A[i],k);
    }
    ll z=fac.size();
    For(i,z){
    	GC[i].resize(z);
    	For(j,z){
    		GC[i][j]=__gcd(fac[i],fac[j]);
    	}
    }
    
    For(i,z){
        dp[0][i]=INF;
        dp2[n+1][i]=INF;
    }
    dp[0][0]=0;
    dp2[n+1][0]=0;
    for(ll i=1;i<=n;++i){
        ll z=B[i];
        ll X=idx[z];
        ll v1=0;
        for(auto e:fac){
            ll y=GC[X][v1];
            dp[i][v1]=min(dp[i-1][v1],dp[i-1][idx[e/y]]+A[i]);
            ++v1;
        }
        
    }
    for(ll i=n;i>=1;--i){
        ll z=B[i];
        ll X=idx[z];

        ll v1=0;
        for(auto e:fac){
            ll y=GC[X][v1];
            dp2[i][v1]=min(dp2[i+1][v1],dp2[i+1][idx[e/y]]+A[i]);

            ++v1;
            
        }
        
        
        
    }
    
    For(zzzz,q){
        ll l,r;
        cin>>l>>r;
        ll i=0,j=z-1;
        ll res=INF;
        while(i<z)
        {
            res=min(res,dp[l-1][i]+dp2[r+1][j]);
            
            ++i;
            --j;
        }
        if (res==INF) res=-1;
        cout<<res<<endl;
    }
}
signed main(){
    fio;
    ll t=1;
    while(t--) {
        solve();
    }
}