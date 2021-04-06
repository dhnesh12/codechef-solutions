#include <bits/stdc++.h>
using namespace std;

#define mx 50000000
typedef long long int ll;

vector<ll>V;
bool prime[mx+5];

void sieve()
{
    V.push_back(0);
    V.push_back(2);
    for (ll i=4; i<=mx; i+=2)
        prime[i]=true;
    for (ll i=3; i<=mx; i+=2)
    {
        if (!prime[i])
        {
            V.push_back(i);
            for (ll j=i*i; j<=mx; j+=(2*i))
                prime[j]=true;
        }
    }
}

ll cnt (ll m, ll p)
{
    ll r=0;
    while (m/p)
    {
        r+=m/p;
        m/=p;
    }
    return r;
}

ll range(ll p, ll lo, ll hi, ll t)
{
    ll mid,L,R;
    if (lo>hi) return -1;
    if (t<p)
    {
        L=max(lo,t*p);
        R=min(hi,t*p+p-1);
//        cout << L << " " << R << endl;
        if (L>R)return -1;
        else return L;
    }
    while (lo<hi)
    {
        mid=(lo+hi)/2;
        if (cnt(mid,p)>=t)
            hi=mid;
        else lo=mid+1;
    }
    if (cnt(lo,p)==t)return lo;
    else return -1;
}

int main()
{
    sieve();
    ll T;
    scanf("%lld",&T);
    while (T--)
    {
        ll low,high,plow,phigh,t,ans=0,Lf,Rt;
        scanf("%lld%lld%lld%lld%lld",&low,&high,&plow,&phigh,&t);
        for (ll i=plow;i<=phigh;i++)
        {
            Lf=range(V[i],low,high,t);
//            cout << "\t" << Lf << endl;
            if (Lf==-1)continue;
//            cout << "\t\t" << (Lf+V[i]-1) << endl;
            Rt=min(high,V[i]*(Lf/V[i])+V[i]-1);
//            cout << Lf << " " << Rt << endl;
            ans+=Rt-Lf+1;
            low=Rt+1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
