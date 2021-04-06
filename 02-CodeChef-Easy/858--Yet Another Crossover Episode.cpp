#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pb push_back
#define pp pop_back
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define f0(i,a,n) for(i=a;i<n;i++)
#define f1(i,a,b) for(i=a;i<=b;i++)
#define all(v) sort(v.begin(),v.end());
#define stp setprecision
#define nl endl
#define I insert
#define ipt(a,n) for(i=0;i<n;i++)cin>>a[i];
#define pll pair<ll,ll>
#define pii pair<int,int>
#define vl vector<ll>
#define mp map<ll,ll>
#define sr(a,n) sort(a,a+n);
#define cx(x) cout<<x<<"\n";
#define cy(x) cout<<x<<" ";
#define cn cout<<"No\n";
#define cw cout<<"Yes\n";
#define bs binary_search
#define S second
#define F first
#define pi 3.141592653589793238
#define ct cout<<"\n"
ll m=1e5;
void solve()
{
    ll n;
    cin>>n;
        vector<ll>v;
        while(1){
            if(n>=m-1){
                v.pb(m);
                v.pb(m-1);
                v.pb(1);
                n-=m-2;
            }
            else{
                v.pb(n+1);
                v.pb(n+2);
                break;
            }
        }
        cout<<v.size()<<"\n";
        for(auto it:v)cout<<it<<" ";
        cout<<"\n";


}
int main()
{
    fast;
    //prime();
    ll t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
}
