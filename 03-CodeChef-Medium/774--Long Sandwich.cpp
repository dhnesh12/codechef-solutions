#include <bits/stdc++.h>
using namespace std;
#define INF 2000000000
typedef long long int ll;
typedef pair<ll,ll> ii;
typedef pair<ii,ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define getbit(n,i) (((n)&(1LL<<(i)))!=0)
#define setbit0(n,i) ((n)&(~(1LL<<(i))))
#define setbit1(n,i) ((n)|(1LL<<(i)))
#define lastone(n) ((n)&(-(n)))
#define read freopen("debug//in.txt","r",stdin)
#define write freopen("debug//out.txt","w",stdout)
#define DBG(a) cerr<<#a<<" ->->->-> "<<a<<"\n"
#define fi first
#define se second
#define PI (acos(-1))
#define fastread ios::sync_with_stdio(false);cin.tie(NULL)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define mod (1000000007)
#define asz 100005
template<class T,class V> ostream& operator<<(ostream &s,pair<T,V> a)
{
    s<<a.fi<<' '<<a.se;
    return s;
}

const int N = 1e3+5;
namespace COMB
{
    ll bigmod(ll a,ll p, ll m)
    {
        ll res=1,x=a;
        while(p)
        {
            if(p&1)res=(res*x)%m;
            x=(x*x)%m;
            p>>=1;
        }
        return res;
    }

    ll fact_mod_p(ll n,ll p,ll md,vi &f)
    {
        return bigmod(f[md-1],n/md,md)*f[n%md]%md;
    }

    ll extended_euclid(ll a,ll b,ll &x,ll &y)
    {
        if(a==0)
        {
            x=0,y=1;
            return b;
        }
        ll x1,y1;
        ll ans=extended_euclid(b%a,a,x1,y1);
        x=y1-(b/a)*x1;
        y=x1;
        return ans;
    }

    ll nCk_p(ll n,ll k,ll r,ll p,ll md,vi &f)
    {
        ll ans = fact_mod_p(n,p,md,f),ik,ir;
        extended_euclid(fact_mod_p(k,p,md,f),md,ik,ir);
        ik = (ik%md+md)%md;
        ans = ans*ik%md;
        extended_euclid(fact_mod_p(r,p,md,f),md,ir,ik);
        ir = (ir%md+md)%md;
        ans = ans*ir%md;
        return ans;
    }

    ll lp(ll n,ll p)
    {
        ll ret = 0;
        while(n)ret+=(n/=p);
        return ret;
    }
    ll nCk_mod_p_a(ll n,ll k,ll p,ll a)
    {
        if(n<k)return 0;
        ll md = 1;
        for(int i=0; i<a; i++)md*=p;
        ll ans = 1, sg = (p==2&&a>=3?1:-1);
        ll r = n-k;
        ll e = bigmod(p,lp(n,p)-lp(k,p)-lp(r,p),mod);
        vi f(md);
        f[0] = 1;
        for(int i=1; i<md; i++)f[i] = f[i-1]*(i%p==0?1:i)%md;
        int cnt = 0;
        while(n)
        {
            cnt++;
            if(cnt>=a-1&&n%p<k%p)ans*=sg;
            ans = ans*nCk_p(n%md,k%md,r%md,p,md,f)%md;
            n/=p,k/=p,r/=p;
        }
        ans = (ans+md)%md*e%md;
        return ans;
    }
    ll mult(ll a, ll b, ll md)
    {
        ll result = 0;
        while (b)
        {
            if (b & 1)
                result = (result + a) % md;
            a = (a + a) % md;
            b >>= 1;
        }
        return result;
    }

    ii CRT(vector<ii> &v)
    {
        int n=v.size();
        ii imp= {-1,-1};
        if(n==0)return imp;
        ii cur=v[0];
        for(int i=1; i<n; i++)
        {
            ll g=__gcd(cur.second,v[i].second);
            if(cur.first%g!=v[i].first%g)return imp;
            ll a,b;
            extended_euclid(cur.second/g,v[i].second/g,a,b);
            ll l=cur.second/g*v[i].second;
            a%=l,b%=l;
            if(a<0)a+=l;
            if(b<0)b+=l;
            ll u=(mult(mult(cur.second/g,v[i].first,l),a,l)+mult(mult(cur.first,v[i].second/g,l),b,l))%l;
            cur= {u,l};
        }
        return cur;
    }
    ll nCk_any_mod(ll n,ll k,ll md)
    {
        if(n<k||k<0)return 0;
        if(md <= 1) return 0;
        vii all;

        for(int i=2; i*i<=md; i++)
        {
            int a = 0;
            ll m = 1;
            while(md%i==0)md/=i,a++,m*=i;

            if(a)all.emplace_back(nCk_mod_p_a(n,k,i,a),m);
        }

        if(md!=1)all.emplace_back(nCk_mod_p_a(n,k,md,1),md);
        return CRT(all).fi;

    }
};

using namespace COMB;
int main()
{
    fastread;
#ifdef FILE_IO2
    read;
    write;
#endif
    int T=1;

    cin>>T;
    for(int qq=1; qq<=T; qq++)
    {
        ll n,k,m;
        cin>>n>>k>>m;
        ll a = (n+k-1)/k;
        cout<<a<<' '<<nCk_any_mod(a+a*k-n-1,a*k-n,m)<<endl;
    }
}

