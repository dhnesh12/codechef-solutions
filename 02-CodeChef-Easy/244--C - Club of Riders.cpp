// Start Time:
#include<bits/stdc++.h>
using namespace std;
#define ff                first
#define ss                second
#define MX                100005
#define ll                long long
#define pb                push_back
#define pi                acos(-1.0)
#define PQ                priority_queue
#define mod               1000000007
#define eps               1/1000000000
#define pii               pair<int,int>
#define pll               pair<ll,ll>
#define endl              "\n"
#define Fast              ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define bug(a)            cout<<#a<<":"<<a<<endl
#define TC(tc)            cout<<"Case "<<tc++<<": "
#define all(x)            (x).begin(),(x).end()
#define allr(x)           (x).rbegin(),(x).rend()
#define MOD(a,b)          (a%mod * b%mod)%mod;
#define mem(a,b)          memset(a, b, sizeof(a))
#define double_print(x,a) cout<<fixed<<setprecision(x)<<a<<endl
ll tc=1;

int main()
{
    ll t;
    cin>>t;
    while(t--)
    {
        ll ks,kp;
        cin>>ks>>kp;
        ll kid=ks*kp;
        ll n;
        cin>>n;
        vector<ll>v(n),w(n);
        for(ll &x:v)
            cin>>x;
        for(ll &x:w)
            cin>>x;

        sort(all(v));
        sort(all(w));
        TC(tc);
        ll ans=1;
        for(int i=0; i<n; i++)
        {
            ll x=kid/v[i];
            ll y=lower_bound(all(w),x+1)-w.begin();
            ll baki=max(0ll, n-y-i);
            ans=MOD(ans,baki);
        }

        cout<<ans<<endl;
    }

    return 0;
}
