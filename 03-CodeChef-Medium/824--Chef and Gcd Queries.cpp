#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long

using namespace __gnu_pbds;
typedef tree<ll, null_type, less<ll>, rb_tree_tag,tree_order_statistics_node_update>ordered_set;

void my_dbg() { cout << endl; }
template<typename Arg, typename... Args> void my_dbg(Arg A, Args... B) 
{ cout << ' ' << A; my_dbg(B...); }
#define dbg(...) cout << "(" << #__VA_ARGS__ << "):", my_dbg(__VA_ARGS__)

#define fast() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define rep(i,ini,n) for(ll i=ini;i<(int)n;i++)
#define all(x) x.begin(),x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define tc   int tt; cin>>tt; while(tt--)
#define gcd __gcd
#define endl "\n"
#define inf INT_MAX
#define ninf INT_MIN

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define PI 3.14159265358979323846264

const ll M =1e9+7;
const int N = 1e5+7;

ordered_set s[N];
vector<ll>divi[N];

void update(ll ele,ll idx)
{
    ll n=divi[ele].size();

    rep(i,0,(1<<n))
    {
        ll sum=1;
        rep(j,0,n)
        {
            if(i&(1<<j))
            sum*=divi[ele][j];

            if(sum>100000)
            break;
        }

        if(sum<=100000)
        s[sum].insert(idx);
    }
}

void remove(ll ele,ll idx)
{
    ll n=divi[ele].size();

    rep(i,0,(1<<n))
    {
        ll sum=1;
        rep(j,0,n)
        {
            if(i&(1<<j))
            sum*=divi[ele][j];

            if(sum>100000)
            break;
        }

        if(sum<=100000)
        s[sum].erase(idx);
    }
}

int main()
{
    fast();

    rep(i,2,N)
    {
        if(divi[i].size()==0)
        for(ll j=i;j<N;j+=i)
        divi[j].pb(i);
    }

    ll n,q;
    cin>>n;

    ll a[n+1];

    rep(i,1,n+1)
    {
        cin>>a[i];

        update(a[i],i);
    }
    
    cin>>q;

    while(q--)
    {
        ll type;
        cin>>type;

        if(type==1)
        {
            ll x,y;
            cin>>x>>y;

            remove(a[x],x);

            a[x]=y;

            update(a[x],x);
        }
        else if(type==2)
        {
            ll l,r,g;
            cin>>l>>r>>g;

            ll ans=r-l+1;

            ll n=divi[g].size();

            rep(i,0,(1<<n))
            {
                ll res=1;
                ll cnt=0;

                rep(j,0,n)
                {
                    if(i&(1<<j))
                    {
                        res*=divi[g][j];
                        cnt++;

                        if(res>100000)
                        break;
                    }
                }

                if(res>1&&res<=100000)
                {
                    ll temp=s[res].order_of_key(r+1)-s[res].order_of_key(l);

                    if(cnt%2)
                    ans-=temp;
                    else ans+=temp;
                }
            }

            cout<<ans<<endl;
        }
    }
return 0;
}