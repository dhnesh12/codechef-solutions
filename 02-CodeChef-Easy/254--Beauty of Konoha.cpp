// Start Time:
#include<bits/stdc++.h>
using namespace std;
#define ff                first
#define ss                second
#define MX                200005
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


int main()
{
    ll t;
    cin>>t;
    while(t--)
    {
        ll n;
        cin>>n;
        ll dis[n+5],deg[n+5];
        for(int i=0; i<n+5; i++)
        {
            dis[i]=0,deg[i]=0;
        }

        ll odd=0,even=1,ans=0;
        for(int i=2; i<=n+1; i++)
        {
            ll x;
            cin>>x;
            deg[i]=1;
            dis[i]=dis[x]+1;
            if(dis[i]%2==0)
            {
                even++;
                if(deg[x]==1)
                    odd--;
            }
            else
            {
                odd++;
                if(deg[x]==1)
                    even--;
            }
            deg[x]++;
            ans+=max(even,odd);
        }

        cout<<ans<<endl;
    }

    return 0;
}
