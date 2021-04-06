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
void solve()
{
    ll a,m,i,j;
    cin>>a>>m;
    //check factors of m
    ll s=sqrt(m);
    set<ll>ans;
    /*if(m%(a+1)==0)
    {
        ans.I(m/(a+1));
    }*/
    for(i=1;i<=s;i++)
    {
        if(m%i==0)
        {
            ll p=m/i-1;
            p=p*i;
            if(p!=0){
            if(p%a==0)
            {
                ll z=p/a;
                if(z%i==0&&z>=i)
                    ans.I(z);
            }}
            ll c=m/i;
            p=m/c-1;
            p=p*c;
            if(p!=0){
            if(p%a==0)
            {
                ll z=p/a;
                if(z%c==0&&z>=c)
                    ans.I(z);
            }}

        }
    }
    cx(ans.size())
    for(auto it:ans)
        cout<<it<<" ";
    ct;

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
