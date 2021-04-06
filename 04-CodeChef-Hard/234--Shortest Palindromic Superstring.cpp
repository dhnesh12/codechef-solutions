#include<bits/stdc++.h>

using namespace std;

#define ll long long 
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mkp make_pair
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define ff first
#define ss second
#define endl "\n"
#define MOD 1000000007
#define MOD1 998244353
#define inf 1e18

ll GCD(ll x,ll y){if(y==0)return x;return GCD(y,x%y);}
ll LCM(ll x,ll y){return (x*y)/(GCD(x,y));}
ll LOGK(ll x,ll k){if(x>=k)return 1+LOGK(x/k,k);return 0;}
ll MPOW( ll a, ll b, ll m) { if(b==0) return 1; ll x=MPOW(a,b/2,m); x=(x*x)%m; if(b%2==1) x=(x*a)%m; return x;}
ll MINV(ll a,ll m) {return MPOW(a,m-2,m);}

class pnc{
  ll FACT_MAX,MODU;
  vector<ll> fact;
public:
  pnc( ll n, ll m) { FACT_MAX = n; fact.resize(FACT_MAX); MODU = m; MFACT_INIT(MODU);}
  void MFACT_INIT( ll m) { fact[0]=1; for(ll i=1;i<FACT_MAX;++i) fact[i]=(i*fact[i-1])%MODU;}
  ll MFACT( ll n) { return fact[n];}
  ll PERM( ll n, ll r) { return (fact[n]*::MINV(fact[n-r],MODU))%MODU;}
  ll COMB( ll n , ll r) { return (PERM(n,r)*::MINV(fact[r],MODU))%MODU;}
};

ll ans;

string rev(string s)
{
    reverse(s.begin(),s.end());
    return s;
}

ll pre(string s)
{
    if(s==rev(s))
    return 0;

    return 1+(pre(s.substr(1,s.size()-1)));
}

ll suf(string s)
{
    if(s==rev(s))
    return 0;

    return 1+(suf(s.substr(0,s.size()-1)));
}

void solve(string s)
{
    ans=min(ans,(ll)s.size()+pre(s));
    ans=min(ans,(ll)s.size()+suf(s));
}

void calc(string x,string y)
{
    ll nox=x.size();
    ll noy=y.size();

    string str=x+'*'+y;
    ll n=str.size();

    vector<ll> pf(n,0);

    ll ok=0;

    for(ll i=1;i<n;i++)
    {
        ll j=pf[i-1];

        while(j>0 && str[j]!=str[i])
        {
            j=pf[j-1];
        }

        if(str[j]==str[i])
        {
            j++;
        }

        pf[i]=j;

        if(pf[i]==nox)
        ok=1;
    }

    string temp=y;

    for(ll i=pf[n-1];i<nox && !ok;i++)
    temp+=str[i];

    solve(temp);

}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);    

    ll test=1;
    cin>>test;
    while(test--)
    {
        ans=inf;

        string s,t;
        cin>>s>>t;

        calc(s,t);
        calc(s,rev(t));
        calc(rev(s),t);
        calc(rev(s),rev(t));

        calc(t,s);
        calc(rev(t),s);
        calc(t,rev(s));
        calc(rev(t),rev(s));

        cout<<ans<<endl;
    }
}